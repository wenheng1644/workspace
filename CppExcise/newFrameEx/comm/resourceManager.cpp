
#include "resourceManager.h"


void ResourceManager::onCallMessage(google::protobuf::Message *msg)
{
    __CmdDispatch.onCallMessage(msg);
}

