#include "netcommhead.h"
#include "../logic/user.h"


void onchatMessageCmd(cmd::chatMessageCmd* msg, user_ptr user)
{
    if(!user)
    {
        printf("onchatMessageCmd | user point error");
        return;
    }
    user->onChatContentMessage(msg);
    // printf("onchatMessageCmd | name = %s, content = %s, status = %d\n", msg->GetTypeName().c_str(), msg->content().c_str(), msg->status());
}