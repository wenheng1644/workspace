
#include "resourceManager.h"

ResourceManager::ResourceManager() : m_works(2)
{
    init_WorkRunner();
}

void ResourceManager::onCallMessage(const netMsg& msg, user_ptr user)
{
    __CmdDispatch.onCallMessage(msg, user);
}

void ResourceManager::post(NETWORK_TYPE tp, std::function<void()> f)
{
    if(tp == NET_IO)
        __netRunner.post(f);
    else if(tp == NET_WORK)
    {
        for(auto& work : m_works)
            work.post(f);
    }
}

void ResourceManager::init_WorkRunner()
{
    // m_workRunner.start(1);
    for(auto& work : m_works)
        work.start(1);


    __netRunner.start(3);
}
