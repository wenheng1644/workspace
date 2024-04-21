//
// Created by ADMIN on 24-4-16.
//

#ifndef SUNNET_SERVICE_H
#define SUNNET_SERVICE_H

#pragma once

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
    std::shared_ptr<BaseMsg> PopMsg();

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
