//
// Created by wenheng on 23-4-9.
//

#ifndef BOOST_ASIO_NEW_NETMSG_H
#define BOOST_ASIO_NEW_NETMSG_H

#define NETBODYLEN 1024
#include "iostream"
#include "memory"
#include "cstring"


#pragma (1)

//數據消息
struct dataInfo
{
    char ip[20];
    char name[20];
    time_t times;
};

struct netHead
{
    u_short     len;        //包长度
    u_char      type;       //消息类型
    u_short     version;    //版本号
    u_short     checknum;   //校验码 len | type ^ version
    dataInfo    info;

    netHead() { std::memset(this, 0, sizeof(netHead));}
};

struct netMsg
{
    netHead head;   //数据头
//    std::shared_ptr<char> body;     //数据体
    char body[NETBODYLEN];
    netMsg() {
        memset(&head, 0, sizeof(head));
        memset(body, 0, sizeof(body));
    }

    netMsg(const std::string& ip, const std::string& name, const std::string content)
    {
        head.len = strlen(content.c_str());
        head.type = 1;
        head.version = 1;
        memcpy(head.info.ip, ip.c_str(), strlen(ip.c_str()));
        memcpy(head.info.name, name.c_str(), strlen(name.c_str()));
        head.info.times = time(nullptr);

        head.checknum = makeChceknum(head);

        memcpy(body, content.c_str(), strlen(content.c_str()));
    }

    static u_short makeChceknum(netHead& head);
    static bool isVaildChecknum(netHead& head);
};

#endif //BOOST_ASIO_NEW_NETMSG_H
