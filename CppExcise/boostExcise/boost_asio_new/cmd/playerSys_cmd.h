//
// Created by wenheng on 23-7-6.
//

#ifndef BOOST_ASIO_NEW_PLAYERSYS_CMD_H
#define BOOST_ASIO_NEW_PLAYERSYS_CMD_H

#include "iostream"
#include "memory"

#include "base_cmd.h"
#include "../common/user.h"

#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"

#include "boost/serialization/deque.hpp"

#define PLAYSYS                 1

#define PLAYSYS_LOGIN_RES           1
#define PLAYSYS_LOGIN_RET           2
#define PLAYSYS_CHECKPLAYERINFO_RES 3
#define PLAYSYS_CHECKPLAYERINFO_RET 4
#define PLAYSYS_ONLINEPLAYERS       5
#define PLAYSYS_ONLINEPLAYERS_RET   6

#define PLAYERCONNECT  MAKEVALUE(PLAYSYS_LOGIN_RES, PLAYSYS)    //登录请求包
#define PLAYERCONNECT_RET   MAKEVALUE(PLAYSYS_LOGIN_RET, PLAYSYS)   //登錄返回包
#define PLAYERCHECKINFO MAKEVALUE(PLAYSYS_CHECKPLAYERINFO_RES, PLAYSYS) //查看信息請求包
#define PLAYERCHECKINFO_RET MAKEVALUE(PLAYSYS_CHECKPLAYERINFO_RET, PLAYSYS) //查看信息返回包
#define PLAYERONLINECOUNT   MAKEVALUE(PLAYSYS_ONLINEPLAYERS, PLAYSYS)       //查看在線玩家數量
#define PLAYERONLINECOUNT_RET   MAKEVALUE(PLAYSYS_ONLINEPLAYERS_RET, PLAYSYS)   //返回在線玩家數量

struct playerConnectCmd
{
//    time_t t;
    u_char v1;
    u_char v2;
    u_char v3;

    u_char checkvalue;

    user userInfo;
    playerConnectCmd()
    {
        memset(this, 0, sizeof(*this));
    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & v1;
        ar & v2;
        ar & v3;
        ar & checkvalue;
        ar & userInfo;
    }

    static u_short getConnectCheckValue(const playerConnectCmd& cmd);
    bool isvaild();
};

struct playerConnectCmd_Ret
{
//    time_t  t;
    u_char ret;
    char msg[50];
    playerConnectCmd_Ret()
    {
        memset(this, 0, sizeof(*this));
    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & ret;
        ar & msg;
    }
};

struct playerCheckInfoCmd
{
    char name[30];

    playerCheckInfoCmd()
    {
        memset(this, 0, sizeof(*this));
    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & name;
    }
};

struct playerCheckInfoCmd_Ret
{
    u_char ret;         //0查找失败
    user userInof;
    playerCheckInfoCmd_Ret()
    {
        memset(this, 0, sizeof(*this));
    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & ret;
        ar & userInof;
    }
};

struct playerOnlineCountCmd
{
    u_char state;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & state;
    }
};

//#pragma (1)
struct playerOnlineCount_Ret
{
    short count;  //在線人數, -1則是服務器故障
    char msg[256];  //故障消息
    std::deque<user> users;

    playerOnlineCount_Ret()
    {
//        memset(this, 0, sizeof(*this));
        memset(msg, 0, sizeof(msg));
    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & count;
        ar & msg;
        ar & users;
    }
};



#endif //BOOST_ASIO_NEW_PLAYERSYS_CMD_H
