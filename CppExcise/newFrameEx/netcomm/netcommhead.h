#ifndef NETCOMMHEAD
#define NETCOMMHEAD

#include "google/protobuf/message.h"
#include "google/protobuf/descriptor.h"

#include "boost/noncopyable.hpp"

#include "chatcmd/chatcmd.pb.h"
#include "baseCmd/basecmd.pb.h"

#include "net/netMsg.h"


typedef std::function<void(google::protobuf::Message*)> MessageCB;


void onchatMessageCmd(chatMessageCmd* msg);

#endif