
#include "netMsg.h"


netHead::netHead(u_char dataType, u_char dataSubType, u_int bodyLen)
{
    type = dataType;
    subtype = dataSubType;
    sendtime = time(nullptr);
    len = bodyLen;
    version = 0;
    checkcode = makecheckcode(*this);
}

netHead &netHead::operator=(const netHead &other)
{
    type = other.type;
    subtype = other.subtype;
    sendtime = other.sendtime;
    len = other.len;
    version = other.version;

    checkcode = other.checkcode;
    
    return *this;
}


/*
    校验码算法：
    校验码为两个字节： 高八位为主协议id 并 数据体长度， 低八位为副协议id 并 时间戳

*/
u_short netHead::makecheckcode(const netHead &head)
{
    u_char lowcode = 0;
    lowcode |= head.subtype;
    lowcode |= head.sendtime;

    u_char highcode = head.type | head.len;

    u_short checkcode = (highcode << 8) | lowcode;

    return checkcode;
}

bool netHead::isvaildcheckcode(const netHead& head)
{
    u_short checkcode = makecheckcode(head);

    return checkcode == head.checkcode;
}

netMsg::netMsg(u_char dataType, u_char dataSubType, const std::string &serStr) : 
    head(netHead(dataType, dataSubType, strlen(serStr.c_str()))), datas(serStr)
{
}

netMsg::netMsg(const netMsg &other) : head(other.head), datas(other.datas)
{
}

netMsg &netMsg::operator=(const netMsg &other)
{
    head = other.head;
    datas = other.datas;

    return *this;
}
