//
// Created by ADMIN on 24-4-16.
//

#ifndef SUNNET_MSG_H
#define SUNNET_MSG_H

#pragma once
#include "iostream"
#include "memory"

class BaseMsg
{
public:
    enum TYPE{
        SERVICE = 1,
        SOCKET_ACCEPT = 2,
        SOCKET_RW = 3,
    };

    u_int8_t m_type;
//    char load[999999]{};
    virtual ~BaseMsg() = default;
};

class ServiceMsg : public BaseMsg
{
public:
    u_int32_t m_source;
    std::shared_ptr<char> m_buff;
    size_t m_size;
};

class SocketAcceptMsg : public BaseMsg
{
public:
    int listenfd;
    int clientfd;
};


class SocketRWMsg : public BaseMsg
{
public:
    int fd;
    bool isRead = false;
    bool isWrite = false;
};

#endif //SUNNET_MSG_H
