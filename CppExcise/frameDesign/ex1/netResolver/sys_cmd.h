//
// Created by wenheng on 23年10月5日.
//

#ifndef EX1_SYS_CMD_H
#define EX1_SYS_CMD_H

#include "base_cmd.h"

#define SYSTEM_HEARTBEAT        1   //心跳包

//系统包基类 200
template <u_char subtype = 0>
struct systemCmd : public baseCmd<SYSTEM, subtype>
{
    time_t m_time;

    systemCmd() : baseCmd<SYSTEM, subtype>() {}

    friend QDataStream& operator<<(QDataStream& os, systemCmd<subtype>& cmd);
    friend QDataStream& operator>>(QDataStream& os, systemCmd<subtype>& cmd);
protected:
    virtual QDataStream& serialze(QDataStream& stream) override;
    virtual QDataStream& reSerialze(QDataStream& stream) override;
};

template<u_char subtype>
QDataStream& systemCmd<subtype>::serialze(QDataStream &stream)
{
    baseCmd<SYSTEM, subtype>::serialze(stream);
    stream << u_int(m_time);
    return stream;
}

template<u_char subtype>
QDataStream& systemCmd<subtype>::reSerialze(QDataStream &stream)
{
    baseCmd<SYSTEM, subtype>::reSerialze(stream);
    u_int time;
    stream >> time;

    m_time = time;

    return stream;
}

template<u_char subtype>
QDataStream& operator<<(QDataStream& os, systemCmd<subtype>& cmd)
{
    cmd.serialze(os);
    return os;
}

template<u_char subtype>
QDataStream& operator>>(QDataStream& os, systemCmd<subtype>& cmd)
{
    cmd.reSerialze(os);
    return os;
}


struct systemHeartBeatCmd : public systemCmd<SYSTEM_HEARTBEAT>
{
        u_char state;   //状态码， 目前无用，占位符
    friend QDataStream& operator<<(QDataStream& os, systemHeartBeatCmd& cmd);
    friend QDataStream& operator>>(QDataStream& os, systemHeartBeatCmd& cmd);
protected:
    virtual QDataStream& serialze(QDataStream& stream) override;
    virtual QDataStream& reSerialze(QDataStream& stream) override;
};

#endif //EX1_SYS_CMD_H
