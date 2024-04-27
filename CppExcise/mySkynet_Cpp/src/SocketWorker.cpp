//
// Created by ADMIN on 24-4-21.
//

#include "SocketWorker.h"
#include "Sunnet.h"

#include "iostream"
#include "thread"
#include "fcntl.h"
#include "sys/socket.h"

#include "assert.h"

void SocketWorker::init()
{
    std::cout << "SocketWorker init" << std::endl;

    epollfd = epoll_create(1);

    assert(epollfd > 0);
}

void SocketWorker::operator()()
{
    std::cout << "SokcetWorker loop" << std::endl;

    while(true)
    {
        int const SIZE = 64;
        epoll_event events[SIZE];

        int count = epoll_wait(epollfd, events, SIZE, -1);

        for(int i = 0; i < count; i++)
        {
            std::cout << "read a fd = " << events[i].data.fd << std::endl;
            OnEvent(events[i]);
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void SocketWorker::AddEvent(int fd)
{
    epoll_event ev;
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = fd;

    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) == -1)
    {
        std::cout << "AddEvent fail...." << std::endl;
        return;
    }
}

void SocketWorker::RemoveEvent(int fd)
{
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, nullptr);
}

void SocketWorker::ModifyEvent(int fd, bool epollOut)
{
    epoll_event ev;

    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLET;

    if(epollOut) ev.events |= EPOLLOUT;

    epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &ev);
}

void SocketWorker::OnEvent(epoll_event ev)
{
    std::cout << "SocketWorker: OnEvent" << std::endl;
    int fd = ev.data.fd;
    auto conn = Sunnet::inst->GetConn(fd);
    if(!conn)
    {
        std::cerr << "get fd error = " << fd << std::endl;
        return;
    }

    bool isRead = ev.events & EPOLLIN;
    bool isWrite = ev.events & EPOLLOUT;
    bool isErr = ev.events & EPOLLERR;

    if(conn->m_type == Conn::TYPE::LISTEN)
    {
        if(isRead)
            OnAccept(conn);
    }
    else
    {
        if(isRead || isWrite)
            OnRW(conn, isRead, isWrite);

        if(isErr)
            std::cerr << "SocketWorker::OnEvent | status err --> " << fd << std::endl;
    }

}

void SocketWorker::OnAccept(std::shared_ptr<Conn> conn)
{
    int clientfd = accept(conn->fd, nullptr, nullptr);

    if(clientfd <= 0)
    {
        std::cerr << "SocketWorker::OnAccept | accept err ---> " << clientfd << std::endl;
        return;
    }

    fcntl(clientfd, F_SETFL, O_NONBLOCK);
    Sunnet::inst->AddConn(clientfd, conn->m_serviceid, Conn::TYPE::CLIENT);
    epoll_event ev;
    ev.data.fd = clientfd;
    ev.events = EPOLLIN | EPOLLET;

    if(-1 == epoll_ctl(epollfd, EPOLL_CTL_ADD, clientfd, &ev))
    {
        std::cerr << "set the client fd error: " << clientfd << std::endl;
        return;
    }

    auto msg = std::make_shared<SocketAcceptMsg>();
    msg->clientfd = clientfd;
    msg->listenfd = conn->fd;
    msg->m_type = BaseMsg::TYPE::SOCKET_ACCEPT;

    Sunnet::inst->Send(conn->m_serviceid, msg);
}

void SocketWorker::OnRW(std::shared_ptr<Conn> conn, bool r, bool w)
{
    auto msg = std::make_shared<SocketRWMsg>();
    msg->fd = conn->fd;
    msg->m_type = BaseMsg::TYPE::SOCKET_RW;
    msg->isWrite = w;
    msg->isRead = r;

    Sunnet::inst->Send(conn->m_serviceid, msg);

}
