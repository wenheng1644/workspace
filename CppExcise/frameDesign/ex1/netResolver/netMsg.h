//
// Created by wenheng on 23-4-9.
//

#ifndef BOOST_ASIO_NEW_NETMSG_H
#define BOOST_ASIO_NEW_NETMSG_H

#define NETBODYLEN 1024
#include "iostream"
#include "memory"
#include "cstring"
#include "deque"

#include "boost/asio.hpp"

#define MAXBYTES 1024

typedef std::pair<std::string, size_t> netData;


#pragma (1)

//數據消息
struct dataInfo
{
    char ip[20];
    char name[20];
    time_t times;

    dataInfo()
    {
//        memcpy(this, 0 , sizeof(*this));
        memset(ip, 0, sizeof(ip));
        memset(name, 0, sizeof(name));
    }

};

struct netHead
{
    u_short     len;        //包长度
    u_char      type;       //主消息类型
    u_char      subtype;    //子消息类型
    u_short     version;    //版本号
    u_short     checknum;   //校验码 len | type ^ version
    dataInfo    info;

    netHead() { std::memset(this, 0, sizeof(netHead));}
};

struct netMsg
{
    netHead head;   //数据头
    std::string body;   //数据体字节流
    netMsg() {
        memset(&head, 0, sizeof(head));
    }
    netMsg(const std::string& ip, const std::string& name, const std::string content) : body(content)
    {
        head.len = content.length();
        head.type = 1;
        head.subtype = 1;
        head.version = 1;
        memcpy(head.info.ip, ip.c_str(), strlen(ip.c_str()));
        memcpy(head.info.name, name.c_str(), strlen(name.c_str()));
        head.info.times = time(nullptr);

        head.checknum = makeChceknum(head);
    }

    netMsg(u_char type, u_char subtype, const netData& net) : body(net.first)
    {
        head.len = net.second;
        head.type = type;
        head.subtype = subtype;
        head.version = 1;
        head.info.times = time(nullptr);

        head.checknum = makeChceknum(head);
    }


    static u_short makeChceknum(netHead& head);
    static bool isVaildChecknum(netHead& head);
    static u_short maketypenum(const netHead& head);
};


typedef std::deque<std::shared_ptr<netMsg>> netMsgQueue;
typedef std::shared_ptr<netMsg> netMsgPtr;
typedef boost::system::error_code error_code_type;

#endif //BOOST_ASIO_NEW_NETMSG_H
