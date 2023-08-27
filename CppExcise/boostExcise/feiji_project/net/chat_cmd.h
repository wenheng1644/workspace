//
// Created by wenheng on 23-6-20.
//

#ifndef FEIJI_PROJECT_CHAT_CMD_H
#define FEIJI_PROJECT_CHAT_CMD_H

#include "cmd.h"


#define MAXCHATBYTES 512

#define CHATRES     1   //请求发送聊天内容
#define CHATRET     2   //返回发送聊天内容结果

struct chatCmdRes : public chatSysCmd<CHATRES>
{

    char content[MAXCHATBYTES] = {0};
    time_t t;
    chatCmdRes()
    {
        MAKECMDZEROMEM(this);
    }
};

struct chatCmdRet : public chatSysCmd<CHATRET>
{
    u_char state;
    time_t t;

    chatCmdRet()
    {
        MAKECMDZEROMEM(this);
    }
};



#endif //FEIJI_PROJECT_CHAT_CMD_H
