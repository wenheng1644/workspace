#ifndef CHATMSG_H
#define CHATMSG_H

#define MAXLEN_MSG 256
#define LEN_IP 20
#define LEN_NAME 20

/**
 * 消息结构：
 * ip：固定长度20字节
 * name：固定长度20字节
 * msg：长度上限256字节
 */

#include "stdlib.h"
#include "cstring"

class chatMsg
{
private:
    char m_data[LEN_IP + LEN_NAME + MAXLEN_MSG];
    size_t m_bodyLen;
public:
    chatMsg(){}
    chatMsg(char ip[], char name[], char msg[]);
    ~chatMsg();

    size_t getBodyLen(){
        return m_bodyLen;
    }

    size_t getLen(){
        return LEN_IP + LEN_NAME + m_bodyLen;
    }

    const char* getData() const{
        return m_data;
    }

    char* getData(){
        return m_data;
    }
};

#endif