#ifndef NETCOMMHEAD
#define NETCOMMHEAD

#include "google/protobuf/message.h"
#include "google/protobuf/descriptor.h"

#include "boost/noncopyable.hpp"

#include "chatcmd/chatcmd.pb.h"

#include "net/resolveManager.h"

#include "net/netMsg.h"


typedef std::function<void(google::protobuf::Message*)> MessageCB;


class user;
typedef std::shared_ptr<user> user_ptr;
void onchatMessageCmd(cmd::chatMessageCmd* msg, user_ptr user);

#endif