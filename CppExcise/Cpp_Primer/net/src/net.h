#ifndef MYNET
#define MYNET

#include "sys/socket.h"
#include "sys/types.h"
#include "unistd.h"
#include "arpa/inet.h"
#include <string>
#include <unordered_map>

typedef unsigned short port_t;
const int BYTES = 1024;

namespace my_net
{
    class net
    {
        public:
            net() =delete;
            net(const std::string& ip, port_t port);

            virtual size_t send(int fd, void* buf, size_t bytes, int flag = 0) = 0;
            virtual size_t recv(int fd, void* buf, size_t bytes, int flag = 0) = 0;

            virtual ~net(){}

        protected:
            std::string m_ip;
            port_t m_port;

            int m_fd;
    };

    class tcp : public net
    {
        public:
            tcp(const std::string& ip, port_t port);

            tcp() = delete;
            tcp(const tcp& right) = delete;
            tcp operator=(const tcp& right) = delete;

            bool start();

            size_t send(int fd, void* buf, size_t bytes, int flag = 0) override;
            size_t recv(int fd, void* buf, size_t bytes, int flag = 0) override;

            virtual ~tcp(){}

        private:
            std::unordered_map<int, sockaddr_in> m_clients;

            void readEvent(int fd, int* maxfd, fd_set fds, fd_set* org_set);
            void writeEvent(int fd, fd_set fds, fd_set* org_set);
    };


    class udp : public net
    {
        public:
            udp(const std::string& ip, port_t port);

            udp() = delete;
            udp(const udp& right) = delete;
            udp operator=(const udp& right) = delete;

            size_t send(int fd, void* buf, size_t bytes, int flag = 0) override;
            size_t recv(int fd, void* buf, size_t bytes, int flag = 0) override;

            virtual ~udp() {}
    };
}


#endif