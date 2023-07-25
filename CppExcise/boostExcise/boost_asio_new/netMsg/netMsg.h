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

#include "boost/serialization/access.hpp"
#include <boost/serialization/serialization.hpp>


#define MAXBYTES 1024

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

    friend class boost::serialization::access;

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int _version) {
        ar & ip;
        ar & name;
        ar & times;
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

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int _version) {
        ar & len;
        ar & type;
        ar & subtype;
        ar & version;
        ar & checknum;
        ar & info;
    }
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
        head.len = strlen(content.c_str());
        head.type = 1;
        head.subtype = 1;
        head.version = 1;
        memcpy(head.info.ip, ip.c_str(), strlen(ip.c_str()));
        memcpy(head.info.name, name.c_str(), strlen(name.c_str()));
        head.info.times = time(nullptr);

        head.checknum = makeChceknum(head);

    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & head;
        ar & body;
    }
    static u_short makeChceknum(netHead& head);
    static bool isVaildChecknum(netHead& head);
    static u_short maketypenum(const netHead& head);
};


typedef std::deque<std::shared_ptr<netMsg>> netMsgQueue;
typedef std::shared_ptr<netMsg> netMsgPtr;
#endif //BOOST_ASIO_NEW_NETMSG_H
