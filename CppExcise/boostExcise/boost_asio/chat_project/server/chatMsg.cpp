#include "chatMsg.h"

#include <iostream>

chatMsg::chatMsg(char ip[], char name[], char msg[])
{
    using namespace std;
    size_t msgLen = strlen(msg);

    strncat(m_data, ip, LEN_IP);
    strncat(m_data + LEN_IP, name, LEN_NAME);
    strncat(m_data + LEN_IP + LEN_NAME, msg, msgLen);

    m_bodyLen = msgLen;
}