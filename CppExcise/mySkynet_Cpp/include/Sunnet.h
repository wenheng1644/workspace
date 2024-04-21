//
// Created by ADMIN on 24-4-16.
//

#ifndef MYSKYNET_CPP_SUNNET_H
#define MYSKYNET_CPP_SUNNET_H

#pragma once



#include "Worker.h"
#include "SocketWorker.h"
#include "Service.h"
#include "Conn.h"

#include "vector"
#include "unordered_map"
class Worker;
class Service;


class Sunnet
{
public:
    static Sunnet* inst;

    std::unordered_map<u_int32_t, std::shared_ptr<Service>> m_services;
    u_int32_t m_maxid = 0;
    pthread_rwlock_t m_lock;


public:
    Sunnet();

    void Start();

    void Wait();

    u_int32_t NewService(std::shared_ptr<std::string> type);
    void KillService(u_int32_t  id);

    void Send(u_int32_t id, std::shared_ptr<BaseMsg> msg);
    std::shared_ptr<Service> PopGloablQueue();
    void PushGlobalQueue(std::shared_ptr<Service> svr);

    void CheckAndWakeUp();
    void WokerWait();

    int AddConn(int fd, u_int32_t id, Conn::TYPE type);
    std::shared_ptr<Conn> GetConn(int fd);
    bool removeConn(int fd);

    static std::shared_ptr<BaseMsg> MakeMsg(u_int32_t source, char* buff, int len);
private:
    int WORKER_NUM = 3;
    std::vector<Worker*> m_works;
    std::vector<std::thread*> m_workThreads;

    SocketWorker* m_socketWorker;
    std::thread* m_socketWorkerThread;

    std::queue<std::shared_ptr<Service>> m_globalServices;
    int m_globalLen;
    pthread_spinlock_t m_globalLock;

    std::unordered_map<u_int32_t, std::shared_ptr<Conn>> m_conns;
    pthread_rwlock_t m_connsMtx;

    pthread_mutex_t m_sleepMtx;
    pthread_cond_t m_sleepcond;
    int m_sleepcnt = 0;

    void StartThread();
    void StartSocket();
    std::shared_ptr<Service> GetService(u_int32_t id);
};


#endif //MYSKYNET_CPP_SUNNET_H
