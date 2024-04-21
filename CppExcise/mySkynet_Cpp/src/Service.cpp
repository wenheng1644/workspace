//
// Created by ADMIN on 24-4-16.
//

#include "Service.h"
#include "Sunnet.h"

#include "memory"

Service::Service()
{
    pthread_spin_init(&m_queueLock, PTHREAD_PROCESS_PRIVATE);
    pthread_spin_init(&m_ingloabl_lock, PTHREAD_PROCESS_PRIVATE);
}

Service::~Service()
{
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
}

void Service::OnMsg(std::shared_ptr<BaseMsg> msg)
{
    if(msg->m_type == BaseMsg::SERVICE)
    {
        auto m = std::dynamic_pointer_cast<ServiceMsg>(msg);
        std::cout << "source id = " << m->m_source << " ---> 打印buff: " << m->m_buff << std::endl;

        auto ret = Sunnet::MakeMsg(m_id, new char[999999]{'p', 'i', 'n', 'g', '\0'}, 999999);
        Sunnet::inst->Send(m->m_source, ret);
    }

}

void Service::OnExit()
{
    std::cout << "服务退出..." << std::endl;
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
