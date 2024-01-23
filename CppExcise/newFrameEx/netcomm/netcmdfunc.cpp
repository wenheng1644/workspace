#include "netcommhead.h"


void onchatMessageCmd(google::protobuf::Message* msg)
{
    printf("onchatMessageCmd | name = %s\n", msg->GetTypeName().c_str());
}