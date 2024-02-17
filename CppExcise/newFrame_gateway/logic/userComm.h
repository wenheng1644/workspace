#ifndef USERCOMM
#define USERCOMM

#include "string"

enum Sex
{
    roboot  = 0,
    male    = 1,
    female  = 2,
};

//账号通用数据
struct userComm
{
    std::string     m_account;  //账号
    std::string     m_name;     //名字
    Sex             m_sex;      //性别
    u_char          m_age;      //年龄
    std::string     m_passwd;   //密码
};


#endif