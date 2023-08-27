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