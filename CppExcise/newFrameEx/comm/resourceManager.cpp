
#include "resourceManager.h"

ResourceManager::ResourceManager()
{
    init();
}

void ResourceManager::onCallMessage(google::protobuf::Message *msg)
{
    __CmdDispatch.onCallMessage(msg);
}

void ResourceManager::init()
{
    init_cmdDisPatch();
}

void ResourceManager::init_cmdDisPatch()
{
    std::shared_ptr<CallBackT<chatMessageCmd>> cb1(new CallBackT<chatMessageCmd>(onchatMessageCmd));
    __CmdDispatch.registerCb(chatMessageCmd::descriptor(), cb1);
}
