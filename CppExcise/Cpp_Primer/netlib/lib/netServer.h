//
// Created by wenheng on 2022/7/24.
//

#ifndef NETLIB_NETSERVER_H
#define NETLIB_NETSERVER_H

#define ERROR_SOCK -1
#define BYTES 1024

#include "iostream"
#include "sys/types.h"
#include "sys/socket.h"
#include "sys/epoll.h"
#include "arpa/inet.h"
#include "fcntl.h"
#include "unistd.h"
#include "sys/uio.h"
#include "string"
#include "vector"



class netServer {
public:
    explicit netServer() = delete;
    explicit netServer(std::string ip, short port);
    netServer(const netServer& left) = delete;

    ~netServer();

    netServer& operator=(const netServer& left) = delete;

    bool start();

private:
    std::string m_ip;
    short m_port;
    int m_listenfd;
};


#endif //NETLIB_NETSERVER_H
