//
// Created by wenheng on 23年12月23日.
//

#include "DisPatcher.h"

void DisPatcher::onCallMessage(google::protobuf::Message* msg)
{
    using namespace google::protobuf;

    const Descriptor* descriptor = msg->GetDescriptor();
    auto iter = __cb_hash.find(descriptor);

    if(iter == __cb_hash.end())
    {
//        printf("onCallMessage | 找不到对应回调(%s)....\n", msg->GetTypeName().c_str());
        if(__defalutcb) __defalutcb(msg); 
        return;
    }
    iter->second->onMessage(msg);
}
