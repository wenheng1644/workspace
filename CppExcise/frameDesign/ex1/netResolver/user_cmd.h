//
// Created by wenheng on 23年8月20日.
//

#ifndef CMD_PROJECT_USER_CMD_H
#define CMD_PROJECT_USER_CMD_H

#include "base_cmd.h"

//用户系统子协议序号
#define USERSYS_LOGIN           1       //登录
#define USERSYS_CHAT            2       //聊天
#define USERSYS_CHECKONLINE     3       //在线人数
#define USERSYS_ONLINELIST      4       //在线列表

enum Sex{
    robot   = 0,
    man     = 1,
    lady    = 2,
};

struct userData
{
    Sex sex;
    std::string name;
    u_char m_gmlevel;

    userData(){}
    userData(const userData& o) : sex(o.sex), name(o.name), m_gmlevel(o.m_gmlevel) {}
    ~userData(){}
};

namespace serlizeSpace
{
    template<typename T>
    QDataStream& operator<<(QDataStream& os, QList<T>& data)
    {
        u_int cnt = data.size();
        os << cnt;
        for(T& v : data)
        {
            os << v;
        }
        return os;
    }

//    template<typename T, typename B = int>
//    QDataStream& operator>>(QDataStream& os, QList<T>& data)
//    {
//        u_int cnt = 0;
//        os >> cnt;
//
//        for(u_int i = 0; i < cnt; i++)
//        {
//            T v;
//            os >> v;
//            data.push_back(v);
//        }
//        return  os;
//    }
}

//用户系统基类
template <u_char subtype = 0>
struct baseUserCmd : public baseCmd<USERSYS, subtype>
{
    std::string m_name;
    u_char m_sex;
    time_t m_time;

    baseUserCmd() : baseCmd<USERSYS, subtype>() {}

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

enum LoginStatusType
{
        SUCCESS = 0,
        DATABASE_CONNECTERROR,
        DATABASE_EXCUTEERROR,
        No_ACCOUNT,
        ERROR_PASSWORD,
        REGISTER_HAD_ACCOUNT,
        ERROR_ONLINE,       //该账号在线
};

enum LoginOperatType
{
    TO_LOGIN = 0,       //登录
    TO_REGISTER = 1,    //注册
};

struct userLoginCmd : public baseUserCmd<USERSYS_LOGIN>
{
        std::string m_account;
        std::string m_password;
        u_char m_status;
        u_char m_login_operation;   //执行请求 0登录/1注册
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



struct userCheckOnlineCmd : public baseUserCmd<USERSYS_CHECKONLINE>
{
    size_t m_onlineCnt;
    friend QDataStream& operator<<(QDataStream& os, userCheckOnlineCmd& cmd);
    friend QDataStream& operator>>(QDataStream& os, userCheckOnlineCmd& cmd);
protected:
    virtual QDataStream& serialze(QDataStream& stream) override;
    virtual QDataStream& reSerialze(QDataStream& stream) override;
};

QDataStream& operator<<(QDataStream& os, userCheckOnlineCmd& cmd);
QDataStream& operator>>(QDataStream& os, userCheckOnlineCmd& cmd);

struct userOnlineListCmd : public baseUserCmd<USERSYS_ONLINELIST>
{
    std::vector<userData> m_userList;
    friend QDataStream& operator<<(QDataStream& os, userOnlineListCmd& cmd);
    friend QDataStream& operator>>(QDataStream& os, userOnlineListCmd& cmd);
protected:
    virtual QDataStream& serialze(QDataStream& stream) override;
    virtual QDataStream& reSerialze(QDataStream& stream) override;
};

QDataStream& operator<<(QDataStream& os, userData& data);
QDataStream& operator>>(QDataStream& os, userData& data);



QDataStream& operator<<(QDataStream& os, userOnlineListCmd& cmd);
QDataStream& operator>>(QDataStream& os, userOnlineListCmd& cmd);


#endif //CMD_PROJECT_USER_CMD_H
