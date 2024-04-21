//
// Created by ADMIN on 24-4-16.
//
#include "Worker.h"

#include "iostream"

void Worker::operator()()
{
    while(true)
    {
        std::shared_ptr<Service> svr = Sunnet::inst->PopGloablQueue();

        if(svr)
        {
            svr->ProcessMsgs(eachNum);
            CheckAndPutGloabl(svr);
        }
        else
        {
            Sunnet::inst->WokerWait();
//            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}

void Worker::CheckAndPutGloabl(std::shared_ptr<Service> svr)
{
    if(svr->m_isExist) return;

    pthread_spin_lock(&svr->m_queueLock);
    {
        if(!svr->m_msgQueue.empty())
        {
            Sunnet::inst->PushGlobalQueue(svr);
        }
        else
        {
            svr->SetInGlobal(false);
        }
    }
    pthread_spin_unlock(&svr->m_queueLock);

}
