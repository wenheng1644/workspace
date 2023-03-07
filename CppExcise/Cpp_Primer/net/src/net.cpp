#include "net.h"


my_net::net::net(const std::string& ip, port_t port) : m_ip(ip), m_port(port), m_fd(-1)
{

}

//tcp实现

my_net::tcp::tcp(const std::string& ip, port_t port) : net(ip, port)
{
    net::m_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == m_fd)
        throw std::runtime_error("create fd error");
}

bool my_net::tcp::start()
{
    sockaddr_in addr;
    addr.sin_addr.s_addr = inet_addr(m_ip.c_str());
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);

    if(-1 == bind(m_fd, (sockaddr*)&addr, sizeof addr))
        throw;
    
    if(-1 == listen(m_fd, SOMAXCONN))
        throw;

    printf("server listen~\n");

    fd_set read_set, write_set;
    FD_ZERO(&read_set);
    FD_ZERO(&write_set);

    FD_SET(m_fd, &read_set);
    int maxfd = m_fd;

    while(true)
    {
        fd_set temp_read = read_set;
        fd_set temp_write = write_set;

        timeval tm;
        tm.tv_sec = 5;
        tm.tv_usec = 0;
        int ret = select(maxfd + 1, &temp_read, &temp_write, nullptr, &tm);

        if(-1 == ret)
        {
            printf("select error\n");
            break;
        }
        else if(0 == ret)
        {
            printf("time-out...\n");
            continue;
        }

        for(int i = 0; i < maxfd + 1; i++)
        {
            //读事件处理
            if(FD_ISSET(i, &temp_read))
                readEvent(i, &maxfd, temp_read, &read_set);

            //写事件处理
            if(FD_ISSET(i, &temp_write))
                writeEvent(i, temp_write, &write_set);
        }
    }
}

void my_net::tcp::readEvent(int fd, int* maxfd ,fd_set fds, fd_set* org_set)
{
    if(fd == m_fd)
    {
        sockaddr_in client_addr;
        socklen_t len = sizeof client_addr;
        int clientfd = accept(m_fd, (sockaddr*)&client_addr, &len);

        if(-1 == clientfd)
        {
            printf("accpet error\n");
            return;
        }

        FD_SET(clientfd, org_set);
        
        m_clients[clientfd] = client_addr;

        *maxfd = clientfd > *maxfd ? clientfd : *maxfd;
        printf("per clientfd = %d connected\n", clientfd);
    }
    else
    {
        char buf[BYTES] = {0};
        int bytes = recv(fd, buf, BYTES);

        if(0 == bytes)
        {
            printf("per client closed\n");
            FD_CLR(fd, org_set);

            m_clients.erase(fd);
            close(fd);
            return;
        }

        printf("recv data = %s\n", buf);
    }
}

void my_net::tcp::writeEvent(int fd, fd_set fds, fd_set* org_set)
{

}

size_t my_net::tcp::send(int fd, void* buf, size_t bytes, int flag)
{   
    ::send(fd, buf, bytes, flag);
}

size_t my_net::tcp::recv(int fd, void* buf, size_t bytes, int flag)
{
    ::recv(fd, buf, bytes, flag);
}

//udp实现

my_net::udp::udp(const std::string& ip, port_t port) : net(ip, port)
{
    net::m_fd = socket(AF_INET, SOCK_DGRAM, 0);
}

size_t my_net::udp::send(int fd, void* buf, size_t bytes, int flag)
{
    ::send(m_fd, buf, bytes, flag);
}

size_t my_net::udp::recv(int fd ,void* buf, size_t bytes, int flag)
{
    ::recv(m_fd, buf, bytes, flag);
}