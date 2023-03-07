/*
聊天室服务器
*/

#ifndef CHATROOM
#define CHATROOM

#define INVAILD_SOCKET -1
#define INVAILD_VALUE -1


typedef unsigned short u_short;

#include "string"
#include "cstring"
#include "unordered_map"
#include "iostream"
#include "functional"

#include "pthread.h"
#include "thread"
#include "mutex"
#include "sys/socket.h"
#include "sys/epoll.h"
#include "arpa/inet.h"
#include "sys/types.h"
#include "unistd.h"
#include "fcntl.h"

class chatRoom
{
    static const int MAX_CLIENTS = 100;
    static const int BUF_SIZE = 1024;
public:
    chatRoom() = delete;
    chatRoom(const std::string& ip, u_short port) : m_ip(ip), m_port(port), m_epollfd(-1), m_serfd(-1) {}
    chatRoom(const chatRoom& right) = delete;

    chatRoom& operator=(const chatRoom& right) = delete;
    ~chatRoom() = default;


    void start();
    void close();
    void handle_client(int fd);
private:
    std::string m_ip;
    u_short m_port;
    int m_epollfd;
    int m_serfd;
    std::unordered_map<int, sockaddr_in> m_clientsInfo;
    std::mutex m_mutex;

    void showError(const std::string& msg);
    void setFdNoBlock(int fd);

    
   

};

#endif