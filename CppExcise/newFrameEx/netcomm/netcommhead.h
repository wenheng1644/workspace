#ifndef NETCOMMHEAD
#define NETCOMMHEAD

#include "google/protobuf/message.h"
#include "google/protobuf/descriptor.h"

#include "boost/noncopyable.hpp"

#include "chatcmd/chatcmd.pb.h"


typedef std::function<void(google::protobuf::Message*)> MessageCB;


void onchatMessageCmd(google::protobuf::Message* msg);

#endif