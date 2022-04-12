#ifndef CHATMSG_H
#define CHATMSG_H

#define BODY_LEN 256
#define HEADER_LEN 10

/**
 * 消息结构：
 * 消息头：固定长度10字节（存储消息体字节长度）
 * 消息体：长度上限256字节
 */

#include "stdlib.h"
#include "cstring"

#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"

using namespace boost::asio;

typedef boost::system::error_code error_code_type;

class chatMsg
{
private:
    char m_data[HEADER_LEN + BODY_LEN];
    size_t m_bodyLen;
public:
    chatMsg(){}
    ~chatMsg() {}

    size_t bodyLen(){
        return m_bodyLen;
    }

    void bodyLen(size_t len)
    {
        m_bodyLen = len;
    }

    size_t getLen(){
        return HEADER_LEN + m_bodyLen;
    }

    const char* getData() const{
        return m_data;
    }

    char* getData(){
        return m_data;
    }

    char* body()
    {
        return m_data + HEADER_LEN;
    }

    void encode()
    {
        char head[HEADER_LEN + 1] = "";
        sprintf(head, "%10d", m_bodyLen);
        memcpy(m_data, head, strlen(head));
    }

    bool decode()
    {
        char head[HEADER_LEN + 1] = "";
        memcpy(head, m_data, HEADER_LEN);

        m_bodyLen = atoi(head);
        if(m_bodyLen < 0 || m_bodyLen > BODY_LEN)
        {
            m_bodyLen = 0;
            return false;
        }
        return true;
    }
};

#endif