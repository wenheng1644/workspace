#include "chatRoom.h"

void chatRoom::start()
{
    m_serfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(INVAILD_SOCKET == m_serfd)
    {
        showError("create serfd error");
        exit(-1);
    }

    int opt = 1;
    setsockopt(m_serfd, SOL_SOCKET, SO_REUSEADDR, (void*)&opt, sizeof opt);

    sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8888);
    addr.sin_family = AF_INET;

    if(INVAILD_VALUE == bind(m_serfd, (sockaddr*)&addr, sizeof addr))
    {
        showError("bind error");
        exit(-1);
    }

    m_epollfd = epoll_create(MAX_CLIENTS);
    if(INVAILD_VALUE == m_epollfd)
    {
        showError("create epoll table error");
        exit(-1);
    }

    epoll_event event;
    event.data.fd = m_serfd;
    event.events = EPOLLIN;

    epoll_ctl(m_epollfd, EPOLL_CTL_ADD, m_serfd, &event);

    if(INVAILD_VALUE == listen(m_serfd, MAX_CLIENTS))
    {
        showError("listen error");
        exit(-1);
    }

    std::cout << "server start to listen" << std::endl;

    while(true)
    {
        epoll_event events[MAX_CLIENTS];
        int cnt = epoll_wait(m_epollfd, events, MAX_CLIENTS, -1);

        if(INVAILD_VALUE == cnt)
        {
            if(errno == EINTR) continue;
            showError("epoll_wait error");
            std::cout << "errno = "  << errno << std::endl;
            break;
        }

        for(int i = 0; i < cnt; i++)
        {
            if(events[i].data.fd == m_serfd)
            {
                sockaddr_in client_addr;
                socklen_t len = sizeof client_addr;

                int clientfd = accept(m_serfd, (sockaddr*)&client_addr, &len);
                if(INVAILD_SOCKET == clientfd)
                {
                    showError("accept client error");
                    continue;
                }

                setFdNoBlock(clientfd);
                epoll_event client_event;
                client_event.data.fd = clientfd;
                client_event.events = EPOLLIN | EPOLLET;

                epoll_ctl(m_epollfd, EPOLL_CTL_ADD, clientfd, &client_event);

                m_clientsInfo.insert({clientfd, client_addr});
                std::cout << "client connect: " << inet_ntoa(client_addr.sin_addr) << std::endl;
            }
            else
            {
                int fd = events[i].data.fd;
                auto func = std::bind(&chatRoom::handle_client, this, std::placeholders::_1);
                std::thread t(func, fd);
                t.detach();
            }
        }
    }
    ::close(m_serfd);
}

void chatRoom::handle_client(int fd)
{
//    FILE* readfp = fdopen(fd, "r");
//    FILE* writefp = fdopen(dup(fd), "w");
//
//    if(!readfp || !writefp)
//    {
//        showError("fp transform error");
//        return;
//    }

    while(true)
    {
        char buf[BUF_SIZE] = {0};
        
        int bytes = read(fd, buf,BUF_SIZE - 1);
        if(0 == bytes)
        {
            std::cout << "close per socket" << std::endl;

            std::lock_guard<std::mutex> gurad(m_mutex);
            epoll_ctl(m_epollfd, EPOLL_CTL_DEL, fd, nullptr);
            m_clientsInfo.erase(fd);
            ::close(fd);
            break;
        }
        else if(-1 == bytes)
        {
            if(errno == EAGAIN)
                break;
        }
        else
        {
            std::lock_guard<std::mutex> gurad(m_mutex);
            for(auto iter = m_clientsInfo.begin(); iter != m_clientsInfo.end(); iter++)
            {
                int clientfd = iter->first;
//                if(clientfd == fd) continue;

                write(clientfd, buf, bytes);
            }
            std::cout << "client ip = " << inet_ntoa(m_clientsInfo[fd].sin_addr) << "\tdata = " << buf << std::endl;
        }
    }
//    fclose(readfp);
//    fclose(writefp);
}

void chatRoom::setFdNoBlock(int fd)
{
    int flag = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

void chatRoom::showError(const std::string& msg)
{
    std::cerr << msg << std::endl;
}