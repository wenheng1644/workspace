#include "resolveManager.h"

std::string getSerlizeNetMsgStr(const netMsg &netmsg)
{
    size_t headlen = sizeof(netmsg.head);
    std::string serstr(headlen + netmsg.head.len, 0);
    std::copy((char*)&netmsg.head, (char*)&netmsg.head + headlen, serstr.begin());
    std::copy(netmsg.datas.begin(), netmsg.datas.end(), serstr.begin() + headlen);

    return serstr;
}

