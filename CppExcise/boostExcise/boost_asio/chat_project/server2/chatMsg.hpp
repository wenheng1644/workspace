//
// Created by 文恒 on 2022/4/9.
//

#ifndef SERVER2_CHATMSG_H
#define SERVER2_CHATMSG_H

#define LEN_IP      20
#define LEN_NAME    20
#define LEN_MAXBODY    512

#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <cstring>

class chatMsg {
public:
    chatMsg() : m_Lenbody(0) {}
    chatMsg(char ip[], char name [], char body[])
    {
        using namespace std;
        //先把内存初始化为0
        memset(m_data, 0, LEN_IP + LEN_NAME + LEN_MAXBODY);

        memcpy_s(m_data, LEN_IP, ip, strlen(ip));
        memcpy_s(m_data + LEN_IP, LEN_NAME, name, strlen(name));
        memcpy_s(m_data + LEN_IP + LEN_NAME, LEN_MAXBODY, body, strlen(body));

        m_Lenbody = strlen(body);
    }

    char* data()
    {
        return m_data;
    }

    const char* data() const
    {
        return m_data;
    }

    const char* body()
    {
        return m_data + LEN_IP + LEN_NAME;
    }

    bool available()
    {
        if(strlen(m_data) == 0)
            return false;

        if(strlen(m_data + LEN_IP) == 0)
            return false;

        return true;
    }

    size_t length()
    {
        return LEN_IP + LEN_NAME + m_Lenbody;
    }

    std::tuple<std::string, std::string, std::string> decode()
    {
        using namespace std;

        string ip(m_data,LEN_IP);
        string name(m_data + LEN_IP, LEN_NAME);
        string body(m_data + LEN_IP + LEN_NAME, m_Lenbody);

        return tuple<string, string, string>(ip, name, body);
    }

private:
    char m_data[LEN_IP + LEN_NAME + LEN_MAXBODY];
    size_t m_Lenbody;
};


#endif //SERVER2_CHATMSG_H
