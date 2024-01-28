#include "netcommhead.h"


void onchatMessageCmd(cmd::chatMessageCmd* msg)
{
    printf("onchatMessageCmd | name = %s, content = %s, status = %d\n", msg->GetTypeName().c_str(), msg->content().c_str(), msg->status());
}