//
// Created by ADMIN on 24-4-16.
//

#ifndef SUNNET_SERVICE_H
#define SUNNET_SERVICE_H

#pragma once

extern "C"{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
};


#include <queue>
#include <memory>
#include <thread>
#include <iostream>

#include "Msg.h"



class Service
{
public:
    Service();
    ~Service();

    void OnInit();
    void OnMsg(std::shared_ptr<BaseMsg> msg);
    void OnExit();

    void PushMsg(std::shared_ptr<BaseMsg> msg);

    bool ProcessMsg();
    void ProcessMsgs(int max);

    void SetInGlobal(bool isIn);
private:
    lua_State* m_luaState;

    std::shared_ptr<BaseMsg> PopMsg();

    void OnServiceMsg(std::shared_ptr<ServiceMsg> msg);
    void OnAcceptMsg(std::shared_ptr<SocketAcceptMsg> msg);
    void OnRwMsg(std::shared_ptr<SocketRWMsg> msg);

    void OnSocketData(int fd, const char* buff, int len);
    void OnSocketWritable(int fd);
    void OnSocketClose(int fd);

public:
    u_int32_t m_id;
    std::shared_ptr<std::string> m_type;

    bool m_isExist = false;

    std::queue<std::shared_ptr<BaseMsg>> m_msgQueue;
    pthread_spinlock_t m_queueLock;

    bool m_inGloabl = false;
    pthread_spinlock_t m_ingloabl_lock;

};

#endif //SUNNET_SERVICE_H
