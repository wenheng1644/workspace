#include "resolveManager.h"

std::string getSerlizeNetMsgStr(const netMsg &netmsg)
{
    netHead head = netmsg.head;
    char buff[sizeof(netHead)] = {0};
    memcpy(buff, (char*)&head, sizeof(buff));

    std::string headStr(buff, buff + sizeof(buff));
    std::string serstr = headStr + netmsg.datas;

    return serstr;
}

