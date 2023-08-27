//
// Created by wenheng on 23年8月20日.
//

#ifndef CMD_PROJECT_USER_CMD_H
#define CMD_PROJECT_USER_CMD_H

#include "base_cmd.h"

//用户系统子协议序号
#define USERSYS_LOGIN           1
#define USERSYS_CHAT            2


//用户系统基类
template <u_char subtype = 0>
struct baseUserCmd : public baseCmd<USERSYS, subtype>
{
    std::string m_name;
    u_char m_sex;
    time_t m_time;


    friend QDataStream& operator<<(QDataStream& os, baseUserCmd<subtype>& cmd);
    friend QDataStream& operator>>(QDataStream& os, baseUserCmd<subtype>& cmd);
protected:
    virtual QDataStream& serialze(QDataStream& stream) override;
    virtual QDataStream& reSerialze(QDataStream& stream) override;
};

template<u_char subtype>
QDataStream &baseUserCmd<subtype>::reSerialze(QDataStream &stream) {
    baseCmd<USERSYS, subtype>::reSerialze(stream);

    QString q_str;
    u_char sex;
    u_int  time;

    stream >> q_str >> sex >> time;

    m_name = q_str.toStdString();
    m_sex = sex;
    m_time = time_t(time);

    return stream;
}

template<u_char subtype>
QDataStream &baseUserCmd<subtype>::serialze(QDataStream& stream) {
    baseCmd<USERSYS, subtype>::serialze(stream);
    stream << QString(m_name.c_str()) << m_sex << u_int(m_time);

    return stream;
}

template<u_char subtype = 0>
QDataStream& operator<<(QDataStream& os, baseUserCmd<subtype>& cmd)
{
    return cmd.serialze(os);
}

template <u_char subtype = 0>
QDataStream& operator>>(QDataStream& os, baseUserCmd<subtype>& cmd)
{
    cmd.reSerialze(os);
    return os;
}


struct userLoginCmd : public baseUserCmd<USERSYS_LOGIN>
{
        friend QDataStream& operator<<(QDataStream& os, userLoginCmd& cmd);
        friend QDataStream& operator>>(QDataStream& os, userLoginCmd& cmd);
protected:
    virtual QDataStream& serialze(QDataStream& stream) override;
    virtual QDataStream& reSerialze(QDataStream& stream) override;
};

QDataStream& operator<<(QDataStream& os, userLoginCmd& cmd);
QDataStream& operator>>(QDataStream& os, userLoginCmd& cmd);

struct userChatCmd : public baseUserCmd<USERSYS_CHAT>
{
    std::string m_content;

    friend QDataStream& operator<<(QDataStream& os, userChatCmd& cmd);
    friend QDataStream& operator>>(QDataStream& os, userChatCmd& cmd);
protected:
    virtual QDataStream& serialze(QDataStream& stream) override;
    virtual QDataStream& reSerialze(QDataStream& stream) override;
};

QDataStream& operator<<(QDataStream& os, userChatCmd& cmd);
QDataStream& operator>>(QDataStream& os, userChatCmd& cmd);


#endif //CMD_PROJECT_USER_CMD_H
