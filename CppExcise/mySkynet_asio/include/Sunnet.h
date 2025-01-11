//
// Created by 文恒 on 24-10-6.
//

#ifndef SUNNET_H
#define SUNNET_H
#pragma once


#include <vector>
#include <thread>
// #include "boost/thread.hpp"
#include <map>
#include <unordered_map>
#include <shared_mutex>

#include "Service.h"
#include "Work.h"

#include "Conn.h"
#include "SocketWork.h"

#include "LuaAPI.h"

typedef std::unordered_map<int, std::shared_ptr<ServerArgs>> ServerCofingId2Map;


class Work;

class Sunnet {
public:
    static Sunnet* inst;
    sol::state m_lua_;


    boost::asio::io_service m_io_service;   //网络部份
    std::unordered_map<u_int32_t, std::shared_ptr<tcp::acceptor>> m_accepts;    //键是服务器id， 值是服务器监听器
    std::shared_mutex m_accepts_mutex;


    std::unordered_map<uint32_t, std::shared_ptr<Service>> m_services;
    u_int32_t m_maxId = 0;

    std::shared_mutex m_serviceMutex;

public:
    Sunnet();
    void Start();

    void Wait();

    void CheckAndWakeUp();
    void WorkWait();

    inline  u_int32_t NewService(const char* c_type, u_int32_t config_id)
    {
        std::string typeStr(c_type);
        std::shared_ptr<std::string> type = std::make_shared<std::string>(typeStr);
        return NewService(type, config_id);
    }
    inline u_int32_t NewService(const std::string& type, uint32_t config_id)
    {
        std::shared_ptr<std::string> p_type = std::make_shared<std::string>(type);
        return NewService(p_type ,config_id);
    }

    u_int32_t NewService(std::shared_ptr<std::string> type, u_int32_t config_id);
    u_int32_t NewService(std::shared_ptr<std::string> type, sol::variadic_args& args);
    void SetServiceConfig(int svrid, const ServerArgs& args);

    void KillService(uint32_t id);

    void Send(uint32_t id,std::shared_ptr<BaseMsg> msg);
    std::shared_ptr<Service> PopGlobalQueue();
    void PushGlobalQueue(std::shared_ptr<Service> service);

    //网络部份
    boost::uuids::uuid AddConn(std::shared_ptr<Conn> conn, u_int32_t id , Conn::TYPE type);
    std::shared_ptr<Conn> GetConn(const boost::uuids::uuid& id);
    bool RemoveConn(const boost::uuids::uuid& id);

    bool Listen(u_int32_t serviceId, u_int32_t port, const std::string& ip = "127.0.0.1");

    void CloseConn(const boost::uuids::uuid& id);

    std::shared_ptr<ServerArgs> loadServerArgs(const std::string& type, u_int32_t config_id);
private:
    //工作线程
    int m_WORKERR_NUM = 3;
    std::vector<Work*> m_works_;
    std::vector<std::thread*> m_WorkThreads_;

    //网络线程
    SocketWork* m_socketWork_;
    std::thread* m_socketWorkThread_;


    //全局队列 ---> 有待处理的服务队列
    std::queue<std::shared_ptr<Service>> m_GlobalQueue_;
    std::mutex m_GlobalMutex_;
    int m_globalqueue_len_ = 0;

    //连接字典
    std::unordered_map<boost::uuids::uuid, std::shared_ptr<Conn>> m_Conns_;
    std::shared_mutex m_ConnMutex_;

    std::mutex m_sleep_mutex_;
    std::condition_variable m_sleep_cv_;
    int m_sleep_count_ = 0;

    // lua_State* m_Lua_;  //主线程lua虚拟机

    // std::unordered_map<std::string, ServerCofingId2Map> m_ServerConfigPool;

private:
    void StartLua();
    void StartWork();
    void StartSocketWork();

    std::shared_ptr<Service> GetService(uint32_t id);
};

#endif //SUNNET_H
