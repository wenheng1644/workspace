//
// Created by ADMIN on 24-4-16.
//

#include "Sunnet.h"
#include "iostream"

Sunnet* Sunnet::inst;

Sunnet::Sunnet()
{
    inst = this;
    std::cout << "construct a obj" << std::endl;
}

void Sunnet::Start()
{
    std::cout << "Sunnet system start" << std::endl;

    pthread_rwlock_init(&m_lock, nullptr);
    pthread_spin_init(&m_globalLock, PTHREAD_PROCESS_PRIVATE);

    pthread_cond_init(&m_sleepcond, nullptr);
    pthread_mutex_init(&m_sleepMtx, nullptr);

    pthread_rwlock_init(&m_connsMtx, nullptr);

    StartThread();
    StartSocket();
}

void Sunnet::StartThread()
{
    for(int i = 0; i < WORKER_NUM; i++)
    {
        Worker* w = new Worker;
        w->id = i;
        w->eachNum = 2 << i;

        m_works.push_back(w);

        std::thread* t = new std::thread(*w);
        m_workThreads.push_back(t);

        std::cout << "construct a work thread: " << i << std::endl;
    }
}

void Sunnet::Wait()
{
    for(auto v : m_workThreads)
        v->join();
}

u_int32_t Sunnet::NewService(std::shared_ptr<std::string> type) {
    std::shared_ptr<Service> svr = std::make_shared<Service>();
    svr->m_type = type;
    pthread_rwlock_wrlock(&m_lock);
    {
        svr->m_id = m_maxid;
        m_maxid++;

        m_services.emplace(svr->m_id, svr);
    }
    pthread_rwlock_unlock(&m_lock);

    svr->OnInit();
    return svr->m_id;
}

std::shared_ptr<Service> Sunnet::GetService(u_int32_t id)
{
    std::shared_ptr<Service> svr = nullptr;

    pthread_rwlock_rdlock(&m_lock);
    {
        auto iter = m_services.find(id);
        if(iter != m_services.end())
        {
            svr = iter->second;
        }

    }
    pthread_rwlock_unlock(&m_lock);

    return svr;
}

void Sunnet::KillService(u_int32_t id)
{
    std::shared_ptr<Service> svr = GetService(id);
    if(!svr) return;

    svr->OnExit();
    svr->m_isExist = true;

    pthread_rwlock_wrlock(&m_lock);
    {
        m_services.erase(svr->m_id);
    }
    pthread_rwlock_unlock(&m_lock);
}

std::shared_ptr<Service> Sunnet::PopGloablQueue()
{
    std::shared_ptr<Service> svr = nullptr;

    pthread_spin_lock(&m_globalLock);
    {
        if(!m_globalServices.empty())
        {
            svr = m_globalServices.front();
            m_globalServices.pop();
            m_globalLen--;
        }
    }
    pthread_spin_unlock(&m_globalLock);

    return svr;
}

void Sunnet::PushGlobalQueue(std::shared_ptr<Service> svr)
{
    pthread_spin_lock(&m_globalLock);
    {
        m_globalServices.push(svr);
        m_globalLen++;
    }
    pthread_spin_unlock(&m_globalLock);
}

void Sunnet::Send(u_int32_t id, std::shared_ptr<BaseMsg> msg)
{
    std::shared_ptr<Service> svr = GetService(id);
    if(!svr) return;

    svr->PushMsg(msg);

    bool hasPush = false;

    pthread_spin_lock(&svr->m_ingloabl_lock);
    {
        if(!svr->m_inGloabl)
        {
            PushGlobalQueue(svr);
            svr->m_inGloabl = true;
            hasPush = true;
        }

    }
    pthread_spin_unlock(&svr->m_ingloabl_lock);

    if(hasPush)
        CheckAndWakeUp();

}

std::shared_ptr<BaseMsg> Sunnet::MakeMsg(u_int32_t source, char *buff, int len)
{
    auto msg = std::make_shared<ServiceMsg>();
    msg->m_type = BaseMsg::SERVICE;
    msg->m_source = source;
    msg->m_buff = std::shared_ptr<char>(buff);
    msg->m_size = len;

    return msg;
}

void Sunnet::CheckAndWakeUp()
{
    if(m_sleepcnt == 0) return;

    if(WORKER_NUM - m_sleepcnt <= m_globalLen)
    {
        pthread_cond_signal(&m_sleepcond);
    }
}

void Sunnet::WokerWait()
{
    pthread_mutex_lock(&m_sleepMtx);
    m_sleepcnt++;
    pthread_cond_wait(&m_sleepcond, &m_sleepMtx);
    m_sleepcnt--;

    pthread_mutex_unlock(&m_sleepMtx);
}

void Sunnet::StartSocket()
{
    m_socketWorker = new SocketWorker();
    m_socketWorker->init();

    m_socketWorkerThread = new std::thread(*m_socketWorker);
}

int Sunnet::AddConn(int fd, u_int32_t id, Conn::TYPE type)
{
    auto conn = std::make_shared<Conn>();
    conn->m_type = type;
    conn->fd = fd;
    conn->m_serviceid = id;

    pthread_rwlock_wrlock(&m_connsMtx);
    m_conns.emplace(fd, conn);
    pthread_rwlock_unlock(&m_connsMtx);
    return fd;
}

std::shared_ptr<Conn> Sunnet::GetConn(int fd)
{
    std::shared_ptr<Conn> conn = nullptr;

    pthread_rwlock_wrlock(&m_connsMtx);

    auto iter = m_conns.find(fd);
    if(iter != m_conns.end())
        conn = iter->second;

    pthread_rwlock_unlock(&m_connsMtx);

    return conn;
}

bool Sunnet::removeConn(int fd)
{
    int result;
    pthread_rwlock_wrlock(&m_connsMtx);
    result = m_conns.erase(fd);
    pthread_rwlock_unlock(&m_connsMtx);

    return result == 1;
}
