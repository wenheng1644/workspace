#ifndef NETCOMMHEAD
#define NETCOMMHEAD

#include "google/protobuf/message.h"
#include "google/protobuf/descriptor.h"

#include "boost/noncopyable.hpp"

#include "chatcmd/chatcmd.pb.h"

#include "net/resolveManager.h"

#include "net/netMsg.h"


#define MAKEPROTO(TYPE, SUBTYPE) ((SUBTYPE) | (TYPE << 8))

#define CHATSYS 1
#define CHATSYS_CHAT 1

#define PROTO_CHATSYS_SYS MAKEPROTO(CHATSYS, CHATSYS_CHAT)

typedef std::function<void(google::protobuf::Message*)> MessageCB;


class netMsg;
google::protobuf::Message* getGoogleMessage(const netMsg& msg);

class user;
typedef std::shared_ptr<user> user_ptr;
void onchatMessageCmd(const cmd::chatMessageCmd* msg, user_ptr user);

#endif