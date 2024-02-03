
#include "resourceManager.h"

ResourceManager::ResourceManager() : m_workRunner(1)
{

}

void ResourceManager::onCallMessage(const netMsg& msg, user_ptr user)
{
    
    __CmdDispatch.onCallMessage(msg, user);
}

