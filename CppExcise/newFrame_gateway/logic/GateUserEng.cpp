#include "GateUserEng.h"
#include "thread"

void GateUserEng::push(gateUser_ptr user)
{
    lockGuard_tp lg(m_GateUserMutex);
    m_GateUserLists[user->onlyid()] = user;
}

void GateUserEng::erase(boost::uuids::uuid onlyid)
{
    lockGuard_tp lg(m_GateUserMutex);
    
    auto iter = m_GateUserLists.find(onlyid);
    if(iter == m_GateUserLists.end()) return;

    m_GateUserLists.erase(iter);
}

void GateUserEng::run()
{
    printf("GateUserEng::run | 网关服 用户循环事件loop\n");
    while(true)
    {
        
        processUser();
        // printf("GateUserEng::run | 用户事件循环执行...\n");

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

void GateUserEng::processUser()
{
    lockGuard_tp lg(m_GateUserMutex);

    for(auto iter : m_GateUserLists)
    {
        iter.second->processGate();
        iter.second->processLogic();
    }
}
