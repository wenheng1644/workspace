
#include "resourceManager.h"


void ResourceManager::onCallMessage(google::protobuf::Message *msg, user_ptr user)
{
    __CmdDispatch.onCallMessage(msg, user);
}

