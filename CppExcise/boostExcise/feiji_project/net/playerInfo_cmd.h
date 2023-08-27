//
// Created by wenheng on 23-6-21.
//

#ifndef FEIJI_PROJECT_PLAYERINFO_CMD_H
#define FEIJI_PROJECT_PLAYERINFO_CMD_H

#include "cmd.h"

#define MAXCHATBYTE 1024

#define PLAYERSYSINFORES        1
#define PLAYERSYSINFORET        2


//发送请求
struct playerInfoCmdRes : public playerSysCmd<PLAYERSYSINFORES>
{
    char ip[20];                    //发送者ip
    u_short port;                   //发送者端口号
    char sendname[20];              //发送者名字
    time_t t;                       //发送时间戳

//    static const u_short value = ;
    playerInfoCmdRes(baseCmd<> *pCmd = nullptr)
    {
        if(!pCmd)
            MAKECMDZEROMEM(this);
        else
            memcpy(this, pCmd, sizeof(*this));
    }
};

//发送结果
struct playerInfoCmdRet : public playerSysCmd<PLAYERSYSINFORET>
{
    u_char state;   //处理结果
    time_t t;       //处理时间戳
};

#endif //FEIJI_PROJECT_PLAYERINFO_CMD_H
