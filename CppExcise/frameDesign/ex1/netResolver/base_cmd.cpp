//
// Created by wenheng on 23年8月20日.
//

#include "base_cmd.h"

QDataStream& operator<<(QDataStream& os, BaseCmd& cmd)
{
    os << cmd.type << cmd.subtype;
    return os;
}

QDataStream& operator>>(QDataStream& os, BaseCmd& cmd)
{
    cmd.reSerialze(os);
    return os;
}

netData netQtResolver::getSerializeStrByNet(const netMsg &msg)
{
    std::string serHead((char*)&msg.head, sizeof(netHead));

    std::string totalSerStr = serHead + msg.body;

    return std::make_pair(totalSerStr, sizeof(netHead) + msg.body.length());
}
