//
// Created by 文恒 on 24-10-6.
//

#include "Work.h"
#include <iostream>
#include <Sunnet.h>
#include <unistd.h>

#include "Service.h"

Work::Work() : m_id(0), m_eachNum(0)
{
}

void Work::operator()()
{
    while (true)
    {
        // std::cout << "Work::operator() ---> id = " << m_id << std::endl;
        std::shared_ptr<Service> srv = Sunnet::inst->PopGlobalQueue();
        if (!srv)
        {
            // usleep(100000);
            Sunnet::inst->WorkWait();
        }
        else
        {
            srv->ProcessMsgs(m_eachNum);
            checkAndPushGlobal(srv);
        }
    }
}

void Work::checkAndPushGlobal(std::shared_ptr<Service> srv)
{
    if(srv->m_isExisting)
    {
        std::cout << "Work::checkAndPushGlobal() isExisting ---> id = " << srv->m_id << std::endl;
        return;
    }

    //判断当前服务是否需要重新放回全局队列
    {
        std::lock_guard<std::mutex> lock_guard(srv->m_queueMutex);
        if(!srv->m_MsgQueue.empty())
        {
            Sunnet::inst->PushGlobalQueue(srv);
        }
        else
        {
            srv->SetInGlobal(false);
        }
    }
}
