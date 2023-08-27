//
// Created by wenheng on 23-7-2.
//

#include "base_cmd.h"
#include "playerSys_cmd.h"

u_short playerConnectCmd::getConnectCheckValue(const playerConnectCmd& cmd)
{
    u_char v1 = cmd.v1 & 0x0f;
    u_char v2 = ((cmd.v2 & 0x0f) << 2) & 0x0f;
    u_char v3 = (cmd.v3 & 0x0f) >> 2;

    return v1 ^ (v2 << 2) ^ (v3 << 6) | 0x01;
}

bool playerConnectCmd::isvaild() {

    u_char value = getConnectCheckValue(*this);
    if(value == checkvalue) return true;

    return false;
}


QDataStream& operator<<(QDataStream& o, playcheckLoginCmd& cmd)
{
    QVector<user> users(cmd.otherUsers.size());
    std::copy(cmd.otherUsers.begin(), cmd.otherUsers.end(), users.begin());
    o << cmd.type << cmd.subtype << cmd.userinfo << users;
    return o;
}

QDataStream& operator>>(QDataStream& o, playcheckLoginCmd& cmd)
{
    u_char type;
    u_char subtype;
    user usrinfo;
    QVector<user> users;

    o >> type >> subtype >> usrinfo >> users;

    cmd.type = type;
    cmd.subtype = subtype;
    cmd.userinfo = usrinfo;

    cmd.otherUsers.resize(users.size());
    std::copy(users.begin(), users.end(), cmd.otherUsers.begin());
    return o;
}



playcheckLoginCmd getData(QDataStream& o)
{
    playcheckLoginCmd cmd;
    o >> cmd.type >> cmd.subtype >> cmd.userinfo;

    return cmd;
}

QDataStream& operator<<(QDataStream& o, BaseCmd cmd)
{
    o << cmd.type << cmd.subtype;
    return o;
}

playcheckLoginCmd getCmdBySerStr(const std::string& str, size_t len)
{
    QByteArray byteArray(str.c_str(), len);

    QDataStream o(byteArray);

    std::cout << boost::format("len = %d, data = %s") % byteArray.size() % byteArray.toStdString() << std::endl;

    playcheckLoginCmd cmd;

    o >> cmd;

    return cmd;
}