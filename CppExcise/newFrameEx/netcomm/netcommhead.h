#ifndef NETCOMMHEAD
#define NETCOMMHEAD

#include "google/protobuf/message.h"
#include "google/protobuf/descriptor.h"

#include "boost/noncopyable.hpp"

#include "chatcmd/chatcmd.pb.h"

#include "net/resolveManager.h"

#include "net/netMsg.h"


typedef std::function<void(google::protobuf::Message*)> MessageCB;


void onchatMessageCmd(cmd::chatMessageCmd* msg);

#endif