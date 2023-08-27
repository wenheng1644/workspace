//
// Created by wenheng on 23年8月20日.
//

#include "user_cmd.h"

QDataStream &userLoginCmd::serialze(QDataStream &stream) {
    return baseUserCmd<USERSYS_LOGIN>::serialze(stream);
}

QDataStream &userLoginCmd::reSerialze(QDataStream &stream) {
    baseUserCmd::reSerialze(stream);

    return stream;
}

QDataStream& operator<<(QDataStream& os, userLoginCmd& cmd)
{
    return cmd.serialze(os);
}

QDataStream& operator>>(QDataStream& os, userLoginCmd& cmd)
{
    cmd.reSerialze(os);
    return os;
}


QDataStream &userChatCmd::serialze(QDataStream &stream) {
    baseUserCmd<USERSYS_CHAT>::serialze(stream);
    stream << QString(m_content.c_str());

    return stream;
}

QDataStream &userChatCmd::reSerialze(QDataStream &stream) {
    baseUserCmd::reSerialze(stream);

    QString q_str;
    stream >> q_str;

    m_content = q_str.toStdString();

    return stream;
}

QDataStream& operator<<(QDataStream& os, userChatCmd& cmd)
{
    return cmd.serialze(os);
}

QDataStream& operator>>(QDataStream& os, userChatCmd& cmd)
{
    return cmd.reSerialze(os);
}