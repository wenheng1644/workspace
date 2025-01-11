//
// Created by 文恒 on 24-10-6.
//

#include "Sunnet.h"
#include <iostream>

Sunnet* Sunnet::inst;

Sunnet::Sunnet(){
    inst = this;

    m_WORKERR_NUM = std::thread::hardware_concurrency() - 2;    //除去主线程和网络线程
    // printf("Sunnet::Sunnet() | max core count = %d\n", std::thread::hardware_concurrency());
}

void Sunnet::Start()
{
    std::cout << "Starting Sunnet" << std::endl;
    StartLua();
    StartWork();
    StartSocketWork();
}

void Sunnet::Wait()
{
    std::cout << "Waiting for Sunnet" << std::endl;
    if(m_WorkThreads_[0])
        m_WorkThreads_[0]->join();
}

void Sunnet::CheckAndWakeUp()
{
    if(m_sleep_count_ == 0)
        return;

    if(m_WORKERR_NUM - m_sleep_count_ <= m_globalqueue_len_)
    {
        m_sleep_cv_.notify_all();
    }
}

void Sunnet::WorkWait()
{
    std::unique_lock<std::mutex> unique_lock(m_sleep_mutex_);
    m_sleep_count_++;

    m_sleep_cv_.wait(unique_lock);

    m_sleep_count_--;
}

u_int32_t Sunnet::NewService(std::shared_ptr<std::string> type, u_int32_t config_id)
{
    std::shared_ptr<Service> srv = std::make_shared<Service>();
    srv->m_type = type;
    srv->m_config_id = config_id;
    {
        std::lock_guard<std::shared_mutex> lock_guard(m_serviceMutex);
        srv->m_id = m_maxId;
        m_maxId++;
        m_services.emplace(srv->m_id, srv);
    }

    sol::variadic_args args;
    srv->OnInit(args);
    return srv->m_id;
}

u_int32_t Sunnet::NewService(std::shared_ptr<std::string> type, sol::variadic_args& args)
{
    std::shared_ptr<Service> srv = std::make_shared<Service>();
    srv->m_type = type;
    srv->m_config_id = 1;
    {
        std::lock_guard<std::shared_mutex> lock_guard(m_serviceMutex);
        srv->m_id = m_maxId;
        m_maxId++;
        m_services.emplace(srv->m_id, srv);
    }

    srv->OnInit(args);
    return srv->m_id;
}

void Sunnet::SetServiceConfig(int svrid, const ServerArgs& args)
{
    auto srv = GetService(svrid);
    if(!srv) return;

    srv->OnSetConfig(args);
}

void Sunnet::KillService(uint32_t id)
{
    auto srv = GetService(id);
    if(!srv) return;

    srv->OnExit();
    srv->m_isExisting = true;

    {
        std::lock_guard<std::shared_mutex> lock_guard(m_serviceMutex);
        m_services.erase(id);
    }

}

void Sunnet::Send(uint32_t id, std::shared_ptr<BaseMsg> msg)
{
    std::shared_ptr<Service> srv = GetService(id);
    if(!srv)
    {
        std::cout << "Service not found: " << id << std::endl;
        return;
    }

    srv->PushMsg(msg);

    bool hasPush = false;

    //处理将服务插入到全局队列中
    {
        std::lock_guard<std::shared_mutex> lock_guard(srv->m_InGlobalMutex);
        if(!srv->m_InGlobal)
        {
            PushGlobalQueue(srv);
            srv->m_InGlobal = true;
            hasPush = true;
        }
    }

    if(hasPush)
    {
        CheckAndWakeUp();
    }
}

std::shared_ptr<Service> Sunnet::PopGlobalQueue()
{
    std::shared_ptr<Service> srv = nullptr;

    {
        std::lock_guard<std::mutex> lock_guard(m_GlobalMutex_);
        if(!m_GlobalQueue_.empty())
        {
            srv = m_GlobalQueue_.front();
            m_GlobalQueue_.pop();
            m_globalqueue_len_--;
        }
    }

    return srv;
}

void Sunnet::PushGlobalQueue(std::shared_ptr<Service> service)
{
    {
        std::lock_guard<std::mutex> lock_guard(m_GlobalMutex_);
        m_GlobalQueue_.push(service);
        m_globalqueue_len_++;
    }
}

boost::uuids::uuid Sunnet::AddConn(std::shared_ptr<Conn> conn, u_int32_t id, Conn::TYPE type)
{
    conn->m_server_id = id;
    conn->m_typ = type;

    {
        std::lock_guard<std::shared_mutex > lock_guard(m_ConnMutex_);
        m_Conns_.emplace(conn->m_uuid, conn);
    }
    // conn->run();

    return conn->m_uuid;
}

std::shared_ptr<Conn> Sunnet::GetConn(const boost::uuids::uuid& id)
{
    std::shared_ptr<Conn> conn = nullptr;
    {
        std::lock_guard<std::shared_mutex> lock_guard(m_ConnMutex_);
        auto it = m_Conns_.find(id);
        if(it != m_Conns_.end())
            conn = it->second;
    }
    return conn;
}

bool Sunnet::RemoveConn(const boost::uuids::uuid& id)
{
    int ret;
    {
        std::lock_guard<std::shared_mutex> lock_guard(m_ConnMutex_);
        ret = m_Conns_.erase(id);
    }
    return ret == 1;
}

bool  Sunnet::Listen( u_int32_t serviceId, u_int32_t port,  const std::string& ip)
{
    boost::asio::ip::address addr = boost::asio::ip::address::from_string(ip);

    boost::asio::ip::tcp::endpoint ed(addr, port);
    std::shared_ptr<tcp::acceptor> acceptor = std::make_shared<tcp::acceptor>(m_io_service, ed);
    if(!acceptor) return false;

    {
        std::lock_guard<std::shared_mutex> lock_guard(m_accepts_mutex);
        m_accepts.emplace(serviceId, acceptor);
    }
    m_socketWork_->run(acceptor, serviceId);
    return true;
}

void Sunnet::CloseConn(const boost::uuids::uuid& id)
{
    {
        std::lock_guard<std::shared_mutex> lock_guard(m_ConnMutex_);
        auto it = m_Conns_.find(id);
        if(it == m_Conns_.end()) return;

        it->second->close();
        m_Conns_.erase(it);
    }
}

// std::shared_ptr<ServerArgs> Sunnet::loadServerArgs(const std::string& type, u_int32_t config_id)
// {
//     if (m_ServerConfigPool.count(type) == 0) return nullptr;
//
//     if (m_ServerConfigPool[type].count(config_id) == 0) return nullptr;
//
//     return m_ServerConfigPool[type][config_id];
// }

void Sunnet::StartLua()
{
    m_lua_.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string, sol::lib::table, sol::lib::ffi, sol::lib::math);

    m_lua_.create_named_table("serverMsgMod");


    LuaAPI::Register(m_lua_);

    // loadServerConfig(m_lua_);

    std::string file = "../server/main.lua";

    sol::protected_function_result result = m_lua_.safe_script_file(file.c_str());



    if(result.valid())
    {
        // int sum = result.get<int>();
        std::cout << "[Sunnet::StartLua] ok" << std::endl;
    }
    else
    {
        std::cerr << "[Sunnet::StartLua] error" << std::endl;
    }

}

void Sunnet::StartWork()
{
    for(int i = 0; i < m_WORKERR_NUM; i++)
    {
        Work* w = new Work();
        w->m_id = i;
        w->m_eachNum = 2 << i;

        // boost::thread* wt = new boost::thread(*w);
        std::thread* wt = new std::thread(*w);

        m_works_.push_back(w);
        m_WorkThreads_.push_back(wt);
    }
}

void Sunnet::StartSocketWork()
{
    m_socketWork_ = new SocketWork();
    m_socketWork_->Init();

    m_socketWorkThread_ = new std::thread(*m_socketWork_);
}

std::shared_ptr<Service> Sunnet::GetService(uint32_t id)
{
    std::shared_ptr<Service> srv = nullptr;

    {
        std::lock_guard<std::shared_mutex> lock_guard(m_serviceMutex);
        auto it = m_services.find(id);
        if(it != m_services.end())
            srv = it->second;
    }
    return srv;
}
