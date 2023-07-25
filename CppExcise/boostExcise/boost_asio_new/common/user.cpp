//
// Created by wenheng on 23-7-2.
//

#include "user.h"

user::user(const std::string &name, u_char sex, time_t t) : m_sex(sex), m_login_time(t)
{
    memcpy(m_name, name.c_str(), sizeof(m_name));
}

user &user::operator=(const user &r){
    m_login_time = r.m_login_time;
    m_sex = r.m_sex;

    memcpy(m_name, r.m_name, sizeof(m_name));
    return *this;
}

user::user(const user& r)
{
    if(this == nullptr)
        std::cerr << "user error" << std::endl;
    m_sex = r.m_sex;
    m_login_time = r.m_login_time;
    memcpy(m_name, r.m_name, sizeof(m_name));

}
