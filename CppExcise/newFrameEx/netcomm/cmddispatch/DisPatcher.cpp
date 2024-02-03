//
// Created by wenheng on 23年12月23日.
//

#include "DisPatcher.h"

DisPatcher::DisPatcher()
{
    std::shared_ptr<CallBackT<cmd::chatMessageCmd>> cb1(new CallBackT<cmd::chatMessageCmd>(onchatMessageCmd));
    registerCb(cmd::chatMessageCmd::descriptor(), cb1, PROTO_CHATSYS_SYS);
}

void DisPatcher::onCallMessage(const netMsg& msg, user_ptr user)
{
    using namespace google::protobuf;


    const Descriptor* descriptor = __proto_hash[msg.head.getProtoValue()];
    if(!descriptor) return;

    auto iter = __cb_hash.find(descriptor);

    if(iter == __cb_hash.end())
    {
//        printf("onCallMessage | 找不到对应回调(%s)....\n", msg->GetTypeName().c_str());
        // if(__defalutcb) __defalutcb(msg); 
        return;
    }

    // const Message* protoMsg = google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
    

    iter->second->onMessage(msg, user);
}
