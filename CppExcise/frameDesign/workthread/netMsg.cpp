//
// Created by wenheng on 23年8月30日.
//
#include "netMsg.h"

u_short netMsg::makeChceknum(netHead &head)
{
    u_short checknum = 0;
    checknum = head.len | head.type;
    checknum ^= head.version;

    return checknum;
}

bool netMsg::isVaildChecknum(netHead &head)
{
    u_short value = makeChceknum(head);
    if(value != head.checknum)
        return false;

    return true;
}

u_short netMsg::maketypenum(const netHead& head)
{
    u_short v = head.type | head.subtype << 8;
    return v;
}