//
// Created by wenheng on 23年8月20日.
//

#ifndef CMD_PROJECT_BASE_CMD_H
#define CMD_PROJECT_BASE_CMD_H

#include "iostream"
#include "string"
#include "utility"

#include "boost/format.hpp"

#include "QDataStream"
#include "QString"
#include "QIODevice"

#define MAKEVALUE(subid, id)  (((subid) << 8) | (id))


typedef std::pair<std::string, size_t> netData;

namespace netQtResolver{
    template<typename T>
    netData getNetDataByCmd(T& cmd);

    template<typename T>
    T getCmdByNetData(const netData& net);
}


template<typename T>
netData netQtResolver::getNetDataByCmd(T &cmd)
{
    QByteArray byteArray;
    QDataStream os(&byteArray, QIODevice::ReadWrite);
    os << cmd;

    return std::make_pair(byteArray.toStdString(), byteArray.size());
}

template<typename T>
T netQtResolver::getCmdByNetData(const netData &net)
{
    QByteArray byteArray(net.first.c_str(), net.second);
    QDataStream is(byteArray);

    T cmd;

    is >> cmd;

    return cmd;
}



//命令主协议序号
#define USERSYS           1           //用户信息系统（用户与用户， 用户与服务器的交互）

//命令基类
template <u_char cmd_type = 0, u_char cmd_subtype = 0>
struct baseCmd
{
    u_char type = cmd_type;        //主协议号
    u_char subtype = cmd_type;     //子协议号

    friend QDataStream& operator>>(QDataStream& os, baseCmd& cmd);
protected:
    virtual QDataStream& serialze(QDataStream& stream);
    virtual QDataStream& reSerialze(QDataStream& stream);
};

template<u_char cmd_type, u_char cmd_subtype>
QDataStream &baseCmd<cmd_type, cmd_subtype>::reSerialze(QDataStream &stream) {
    stream >> type >> subtype;
    return stream;
}

template<u_char cmd_type, u_char cmd_subtype>
QDataStream &baseCmd<cmd_type, cmd_subtype>::serialze(QDataStream& stream)
{
//    QByteArray byteArray;
//    QDataStream stream(&byteArray, QIODevice::ReadWrite);

    stream << type << subtype;

    return stream;
}


typedef baseCmd<> BaseCmd;
QDataStream& operator<<(QDataStream& os, BaseCmd& cmd);
QDataStream& operator>>(QDataStream& os, BaseCmd& cmd);


#endif //CMD_PROJECT_BASE_CMD_H
