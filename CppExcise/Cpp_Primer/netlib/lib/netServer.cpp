//
// Created by wenheng on 2022/7/24.
//

#include "netServer.h"

netServer::netServer() : m_ip("127.0.0.1"), m_port(8888), m_listenfd(ERROR_SOCK)
{

}

netServer::netServer(std::string ip, short port) : m_ip(ip), m_port(port), m_listenfd(ERROR_SOCK)
{

}

netServer::~netServer()
{

}

bool netServer::start()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(ERROR_SOCK == listenfd)
    {
        printf("listenfd create error\n");
        return false;
    }

    u_long on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, (char *)&on, sizeof on);
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof on);

    int oldFlag = fcntl(listenfd, F_GETFL, 0);
    int newFlag = oldFlag | O_NONBLOCK;

    if(-1 == fcntl(listenfd, F_SETFL, newFlag))
    {
        printf("fcntl listenfd error\n");
        close(listenfd);
        return false;
    }

    sockaddr_in bind_addr;
    bind_addr.sin_port = htons(m_port);
    bind_addr.sin_addr.s_addr = inet_addr(m_ip.c_str());
    bind_addr.sin_family = AF_INET;
    if(-1 == bind(listenfd, (sockaddr *)&bind_addr, sizeof bind_addr))
    {
        printf("listenfd bind error\n");
        close(listenfd);
        return false;
    }

    if(-1 == listen(listenfd, SOMAXCONN))
    {
        printf("listenfd listen error\n");
        close(listenfd);
        return false;
    }

    epoll_event listen_epoll;
    listen_epoll.data.fd = listenfd;
    listen_epoll.events = EPOLLIN;

    int epollfd = epoll_create(1);

    if(-1 == epollfd)
    {
        printf("epollfd create error\n");
        close(listenfd);
        return false;
    }

    if(-1 == epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &listen_epoll))
    {
        printf("epoll_ctl listenfd error\n");
        close(listenfd);
        return false;
    }

    printf("server start successfully\n");
    while(true)
    {
        std::vector<epoll_event> events;
        events.push_back(listen_epoll);
        int n = epoll_wait(epollfd, &events[0], 1024, 0);

        if(-1 == n)
        {
            if(errno != EINTR && errno != EWOULDBLOCK)
            {
                printf("epoll_wait error\n");
                break;
            }

        }
        else if(0 == n)
        {
            continue;
        }


        for(int i = 0; i < n; i++)
        {
            if(events[i].events & EPOLLIN)
            {
                //有新客户端连接
                if(events[i].data.fd == listenfd)
                {
                    sockaddr_in client_addr;
                    socklen_t len = sizeof client_addr;

                    int clientfd = accept(events[i].data.fd, (sockaddr *)&client_addr, &len);

                    if(clientfd != -1)
                    {
                        int oldFlag_client = fcntl(listenfd, F_GETFL, 0);
                        int newFlag_client = oldFlag_client | O_NONBLOCK;

                        if(-1 == fcntl(clientfd, F_SETFL, newFlag_client))
                        {
                            printf("fcntl listenfd error\n");
                            close(clientfd);
                            continue;
                        }

                        epoll_event client_epoll;
                        client_epoll.data.fd = clientfd;
                        client_epoll.events = EPOLLIN;

                        if(0 == epoll_ctl(epollfd, EPOLL_CTL_ADD, clientfd, &client_epoll))
                            printf("clientfd epoll_ctl successfully~\n");
                        else
                            printf("clientfd epoll_ctl error~\n");
                    }
                }
                else //通信socket读数据
                {
                    char buf[BYTES] = {0} , buf2[BYTES] = {0};
                    iovec bufs[2];
                    bufs[0].iov_base = buf;
                    bufs[0].iov_len = 5;

                    bufs[1].iov_base = buf2;
                    bufs[1].iov_len = 5;
                    int ret = readv(events[i].data.fd, bufs, 2);
                    if(ret <= 0)
                    {
                        epoll_ctl(epollfd, EPOLL_CTL_DEL, events[i].data.fd, 0);
                        close(events[i].data.fd);
                        printf("clientfd = %d read data close\n", events[i].data.fd);
                    }
                    else
                    {
                        printf("clientfd = %d\tdata1: %s\tdata2: %s\n", events[i].data.fd,buf, buf2);
                    }
                }
            }

        }

    }

    close(listenfd);
    return true;
}
