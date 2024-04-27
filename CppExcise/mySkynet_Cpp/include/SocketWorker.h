//
// Created by ADMIN on 24-4-21.
//

#ifndef SUNNET_SOCKETWORKER_H
#define SUNNET_SOCKETWORKER_H

#pragma once

#include "sys/epoll.h"
#include "Conn.h"
#include "memory"
class SocketWorker
{
public:
    SocketWorker() = default;
    void init();

    void operator()();

    void AddEvent(int fd);
    void RemoveEvent(int fd);
    void ModifyEvent(int fd, bool epollOut);
private:
    int epollfd;

    void OnEvent(epoll_event ev);
    void OnAccept(std::shared_ptr<Conn> conn);
    void OnRW(std::shared_ptr<Conn> conn, bool r, bool w);
};

#endif //SUNNET_SOCKETWORKER_H
