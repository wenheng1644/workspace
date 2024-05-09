//
// Created by ADMIN on 24-4-16.
//

#include "Service.h"
#include "Sunnet.h"

#include "memory"
#include "unistd.h"

#include "LuaAPI.h"

Service::Service()
{
    pthread_spin_init(&m_queueLock, PTHREAD_PROCESS_PRIVATE);
    pthread_spin_init(&m_ingloabl_lock, PTHREAD_PROCESS_PRIVATE);
}

Service::~Service()
{
    lua_close(m_luaState);
    std::cout << "服务器引擎关闭: " << m_id << std::endl;
    pthread_spin_destroy(&m_queueLock);
    pthread_spin_destroy(&m_ingloabl_lock);
}

void Service::PushMsg(std::shared_ptr<BaseMsg> msg)
{
    pthread_spin_lock(&m_queueLock);

    m_msgQueue.push(msg);

    pthread_spin_unlock(&m_queueLock);
}

std::shared_ptr<BaseMsg> Service::PopMsg() {
    std::shared_ptr<BaseMsg> ret = nullptr;
    pthread_spin_lock(&m_queueLock);
    {
        if(!m_msgQueue.empty())
        {
            ret =  m_msgQueue.front();
            m_msgQueue.pop();
        }
    }
    pthread_spin_unlock(&m_queueLock);
    return ret;
}

void Service::OnInit()
{
    std::cout << "初始化回调..." <<  std::endl;
//    Sunnet::inst->Listen(8001, m_id);

    m_luaState = luaL_newstate();
    luaL_openlibs(m_luaState);
    LuaAPI::Register(m_luaState);


    std::string file = "../service/" + *m_type + "/init.lua";
    int ret = luaL_dofile(m_luaState, file.data());

    if(ret == 1)
    {
        std::cerr << "run lua fail...  ---> " << lua_tostring(m_luaState, -1) << std::endl;
    }

    lua_getglobal(m_luaState, "OnInit");
    lua_pushinteger(m_luaState, m_id);
    ret = lua_pcall(m_luaState, 1, 0, 0);

    if(ret != 0)
    {
        std::cerr << "run lua error: " << lua_tostring(m_luaState, -1) << std::endl;
    }


}

void Service::OnMsg(std::shared_ptr<BaseMsg> msg)
{
    if(msg->m_type == BaseMsg::SERVICE)
    {
        auto m = std::dynamic_pointer_cast<ServiceMsg>(msg);
        OnServiceMsg(m);
    }
    else if(msg->m_type == BaseMsg::TYPE::SOCKET_ACCEPT)
    {
        auto acceptMsg = std::dynamic_pointer_cast<SocketAcceptMsg>(msg);
        OnAcceptMsg(acceptMsg);
    }
    else if(msg->m_type == BaseMsg::TYPE::SOCKET_RW)
    {
        auto RW_Msg = std::dynamic_pointer_cast<SocketRWMsg>(msg);
        OnRwMsg(RW_Msg);
    }


}

void Service::OnExit()
{
    std::cout << "服务退出..." << std::endl;
    lua_getglobal(m_luaState, "OnExit");
    int ret = lua_pcall(m_luaState, 0, 0, 0);

    if(ret != 0)
    {
        std::cerr << "lua pcall OnExit fail: " << lua_tostring(m_luaState, -1) << std::endl;
    }

    // this->~Service();
}

bool Service::ProcessMsg()
{
    std::shared_ptr<BaseMsg> msg = PopMsg();
    if(msg)
    {
        OnMsg(msg);
        return true;
    }

    return false;
}

void Service::ProcessMsgs(int max)
{
    for(int i = 0; i < max; i++)
    {
        bool ret = ProcessMsg();
        if(!ret) break;
    }

}

void Service::SetInGlobal(bool isIn)
{
    pthread_spin_lock(&m_ingloabl_lock);
    m_inGloabl = isIn;
    pthread_spin_unlock(&m_ingloabl_lock);
}

void Service::OnServiceMsg(std::shared_ptr<ServiceMsg> msg)
{
    std::cout << "source id = " << msg->m_source << " ---> 打印buff: " << msg->m_buff << std::endl;

    if(m_luaState == nullptr) return;
    // int status = lua_status(m_luaState);

    lua_getglobal(m_luaState, "OnServiceMsg");
    lua_pushinteger(m_luaState, msg->m_source);
    lua_pushlstring(m_luaState, msg->m_buff.get(), msg->m_size);

    if(m_isExist == true) return;
    int a = 1;
    int isok = lua_pcall(m_luaState, 2, 0, 0);
    if(isok != 0)
    {
        std::cerr << "[c++] OnServiceMsg error: " << lua_tostring(m_luaState, -1) << std::endl;
    }

    // auto ret = Sunnet::MakeMsg(m_id, new char[999999]{'p', 'i', 'n', 'g', '\0'}, 999999);
    // Sunnet::inst->Send(msg->m_source, ret);
}

void Service::OnAcceptMsg(std::shared_ptr<SocketAcceptMsg> msg)
{
    std::cout << "Service: new conn ---> " << msg->clientfd << std::endl;
    lua_getglobal(m_luaState, "OnAcceptMsg");
    lua_pushinteger(m_luaState, msg->listenfd);
    lua_pushinteger(m_luaState, msg->clientfd);

    int ret = lua_pcall(m_luaState, 2, 0, 0);
    if(ret != 0)
    {
        std::cerr << "[C++] OnAcceptMsg fail: " << lua_tostring(m_luaState, -1) << std::endl;
    }

}

void Service::OnRwMsg(std::shared_ptr<SocketRWMsg> msg)
{
    if(msg->isRead)
    {
        const int Size = 1024;
        char buff[Size] = {0};
        size_t bytes = 0;

        do{
            bytes = read(msg->fd, buff, Size);
            if(bytes > 0)
                OnSocketData(msg->fd, buff, bytes);
        } while (bytes == Size);

        if(bytes == 0 && errno != EAGAIN)
        {
            if(Sunnet::inst->GetConn(msg->fd))
            {
                OnSocketClose(msg->fd);
                Sunnet::inst->CloseConn(msg->fd);
            }
        }
    }

    if(msg->isWrite)
    {
        if(Sunnet::inst->GetConn(msg->fd))
            OnSocketWritable(msg->fd);
    }
}

void Service::OnSocketData(int fd, const char *buff, int len)
{
    std::cout << "OnSocketData: " << fd << ", data: " << buff << std::endl;
    // write(fd, buff, len);
    lua_getglobal(m_luaState, "OnSocketData");
    lua_pushinteger(m_luaState, fd);
    lua_pushlstring(m_luaState, buff, len);

    int ret = lua_pcall(m_luaState, 2, 0, 0);
    if(ret != 0)
    {
        std::cerr << "[C++] OnSocketData: " << lua_tostring(m_luaState, -1) << std::endl;
    } 

}

void Service::OnSocketWritable(int fd)
{
    std::cout << "OnSocketWritable: " << fd << std::endl;
}

void Service::OnSocketClose(int fd)
{
    std::cout << "OnSocketClose: " << fd << std::endl;

    lua_getglobal(m_luaState, "OnSocketClose");
    lua_pushinteger(m_luaState, fd);

    int ret = lua_pcall(m_luaState, 1, 0, 0);
    if(ret != 0)
    {
        std::cerr << "[C++] OnSocketClose: " << lua_tostring(m_luaState, -1) << std::endl;
    } 
}
