//
// Created by wenheng on 23年10月5日.
//

#include "sys_cmd.h"

QDataStream &systemHeartBeatCmd::serialze(QDataStream &stream)
{
    systemCmd<SYSTEM_HEARTBEAT>::serialze(stream);
    stream << state;

    return stream;
}

QDataStream &systemHeartBeatCmd::reSerialze(QDataStream &stream) {
    systemCmd<SYSTEM_HEARTBEAT>::reSerialze(stream);
    stream >> state;

    return stream;
}

QDataStream &operator<<(QDataStream &os, systemHeartBeatCmd &cmd) {
    return cmd.serialze(os);
}

QDataStream &operator>>(QDataStream &os, systemHeartBeatCmd &cmd) {
    return cmd.reSerialze(os);
}
