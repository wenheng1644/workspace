//
// Created by wenheng on 23-6-20.
//

#ifndef FEIJI_PROJECT_CMD_H
#define FEIJI_PROJECT_CMD_H

#include "iostream"
#include "cstring"
#include "queue"
#include "memory"
#include "map"

#include "boost/asio.hpp"
/**
 * 主协议号：1  玩家信息
 *
 *
 *
 *
 */

#define PLAYERSYS           1    //玩家系统
#define CHATSYS             2   //聊天系统


#define MAKEVALUE(id, subid) ((id << 8) | subid)

#define PLAYERINFO_VALE MAKEVALUE(1,1)
#define CHATRES_VALUE   MAKEVALUE(2,1)

template<u_char v1 = 0, u_char v2 = 0>
struct baseCmd{
    u_char id = v1;          //主协议号
    u_char subid = v2;       //子协议号

    u_short len;            //子类部分字节长度
//    static const u_short value = MAKEVALUE(v1, v2);

//    baseCmd()
//    {
////        memset(this, 0, sizeof(*this));
//    }
//    virtual ~baseCmd() {}
};

typedef baseCmd<> bCmd;

#define MAKECMD(classtype,id) template<u_char v1 = 0> struct classtype : public baseCmd<id, v1>{};


MAKECMD(playerSysCmd, PLAYERSYS)
MAKECMD(chatSysCmd, CHATSYS)


#define MAKECMDZEROMEM(point) (memset((char*)point + sizeof(baseCmd), 0, sizeof(*point) - sizeof(baseCmd)))

//typedef std::shared_ptr<baseCmd<>> cmdPtr;
typedef std::queue<bCmd*> cmdQueue;
typedef boost::system::error_code error_code_type;
typedef std::map<size_t, cmdQueue> userCmdMap;


#endif //FEIJI_PROJECT_CMD_H
