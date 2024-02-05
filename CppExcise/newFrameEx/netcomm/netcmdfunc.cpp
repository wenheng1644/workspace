#include "netcommhead.h"
#include "../logic/user.h"
#include "vector"

google::protobuf::Message *getGoogleMessage(const netMsg &msg)
{

    cmd::chatMessageCmd chatMsg;

    google::protobuf::Message * googleMsg = &chatMsg;

    googleMsg->ParseFromString(msg.datas);
    
    return googleMsg;
}

void onchatMessageCmd(const cmd::chatMessageCmd *msg, user_ptr user)
{
    if(!user)
    {
        printf("onchatMessageCmd | user point error");
        return;
    }
    user->onChatContentMessage(msg);
    // printf("onchatMessageCmd | name = %s, content = %s, status = %d\n", msg->GetTypeName().c_str(), msg->content().c_str(), msg->status());
}