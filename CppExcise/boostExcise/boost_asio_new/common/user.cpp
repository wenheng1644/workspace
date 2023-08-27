//
// Created by wenheng on 23-7-2.
//

#include "user.h"

user::user(const std::string &name, u_char sex, time_t t) : m_sex(sex), m_login_time(t), m_name(name)
{
}

user &user::operator=(const user &r){
    m_login_time = r.m_login_time;
    m_sex = r.m_sex;

    m_name = r.m_name;
    return *this;
}

user::user(const user& r)
{
    if(this == nullptr)
        std::cerr << "user error" << std::endl;
    m_sex = r.m_sex;
    m_login_time = r.m_login_time;
    m_name = r.m_name;

}

QDataStream& operator<<(QDataStream& o, user info)
{
    QString q_str(info.m_name.c_str());
    o << q_str << (u_int)info.m_login_time << info.m_sex;
    return o;
}

QDataStream& operator>>(QDataStream& o, user& info)
{
    QString q_str;
    u_int login_time;
    u_char sex;
    o >> q_str >> login_time >> sex;

    info.m_name = q_str.toStdString();
    info.m_login_time = time_t(login_time);
    info.m_sex = sex;

    return o;
}