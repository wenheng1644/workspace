//
// Created by wenheng on 23年8月20日.
//

#include "user_cmd.h"
#include "QtCore/QtCore"

QDataStream &userLoginCmd::serialze(QDataStream &stream) {
    baseUserCmd<USERSYS_LOGIN>::serialze(stream);
    stream << QString(m_account.c_str());
    stream << QString(m_password.c_str());
    stream << m_status;
    stream << m_login_operation;
    return stream;
}

QDataStream &userLoginCmd::reSerialze(QDataStream &stream) {
    baseUserCmd::reSerialze(stream);
    QString account;
    QString password;

    stream >> account;
    stream >> password;
    stream >> m_status;
    stream >> m_login_operation;

    m_account = account.toStdString();
    m_password = password.toStdString();

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

QDataStream &userCheckOnlineCmd::serialze(QDataStream &stream) {
    baseUserCmd<USERSYS_CHECKONLINE>::serialze(stream);
    stream << quint64(m_onlineCnt) ;

    return stream;
}

QDataStream &userCheckOnlineCmd::reSerialze(QDataStream &stream) {
    baseUserCmd::reSerialze(stream);

    quint64 onlineCnt;
    stream >> onlineCnt;

    m_onlineCnt = onlineCnt;
    return stream;
}

QDataStream& operator<<(QDataStream& os, userCheckOnlineCmd& cmd)
{
    return cmd.serialze(os);
}

QDataStream& operator>>(QDataStream& os, userCheckOnlineCmd& cmd)
{
    return cmd.reSerialze(os);
}


QDataStream &operator<<(QDataStream &os, userData &data)
{
    os << data.sex;
    os << QString::fromStdString(data.name);
    os << data.m_gmlevel;

    return os;
}

QDataStream &operator>>(QDataStream &os, userData &data)
{
    os >> data.sex;

    QString name;
    os >> name;

    data.name = name.toStdString();

    os >> data.m_gmlevel;

    return os;
}


QDataStream &userOnlineListCmd::serialze(QDataStream &stream) {
    baseUserCmd<USERSYS_ONLINELIST>::serialze(stream);
    QList<userData> q_onlineList(m_userList.begin(), m_userList.end());

    using namespace serlizeSpace;
    stream << q_onlineList;
    return stream;
}

QDataStream &userOnlineListCmd::reSerialze(QDataStream &stream) {
    baseUserCmd::reSerialze(stream);

    QList<userData> q_onlineList;

    using namespace serlizeSpace;
    stream >> q_onlineList;

    for(const auto& v : q_onlineList)
        m_userList.push_back(v);
//    m_onlineCnt = onlineCnt;
    return stream;
}

QDataStream& operator<<(QDataStream& os, userOnlineListCmd& cmd)
{
    return cmd.serialze(os);
}

QDataStream& operator>>(QDataStream& os, userOnlineListCmd& cmd)
{
    return cmd.reSerialze(os);
}


