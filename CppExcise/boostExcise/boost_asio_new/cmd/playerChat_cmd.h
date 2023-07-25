//
// Created by wenheng on 23-7-6.
//

#ifndef BOOST_ASIO_NEW_PLAYERCHAT_CMD_H
#define BOOST_ASIO_NEW_PLAYERCHAT_CMD_H

#include "iostream"
#include "memory"

#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"



#define CHATSYS                 2

#define CHATSYS_CHATMSG                 1
#define CHATSYS_CHATMSG_RET             2
#define CHATSYS_SENDCHATMSGTOUSER       3
#define CHATSYS_SENDCHATMSGTOUSER_RET   4


#define PLAYERCHATMSG   MAKEVALUE(CHATSYS_CHATMSG, CHATSYS) //聊天请求包
#define PLAYERCHATMSG_RET   MAKEVALUE(CHATSYS_CHATMSG_RET, CHATSYS) //聊天返回包
#define PLAYERSENDUSERCHAT  MAKEVALUE(CHATSYS_SENDCHATMSGTOUSER, CHATSYS)   //请求发送私人聊天信息
#define PLAYERSENDUSERCHAT_RET  MAKEVALUE(CHATSYS_SENDCHATMSGTOUSER_RET, CHATSYS)   //发送私人聊天信息返回


struct playerChatMsgCmd
{
//    time_t t;
    char buff[512];

    playerChatMsgCmd()
    {
        memset(buff, 0 , 512);
    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & buff;
    }
};


struct playerChatMsgCmd_Ret
{
//    time_t t;
    u_char ret;
    char buff[512];

    playerChatMsgCmd_Ret()
    {
        memset(buff, 0, 512);
    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & ret;
        ar & buff;
    }
};

struct playerSendUserChatCmd
{
    char name[30];
    char buff[512];

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & name;
        ar & buff;
    }
};

struct playerSendUserChatCmd_Ret
{
    u_char ret;
    char content[512];

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & ret;
        ar & content;
    }
};

#endif //BOOST_ASIO_NEW_PLAYERCHAT_CMD_H
