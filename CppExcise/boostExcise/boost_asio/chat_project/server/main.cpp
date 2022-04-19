//
// Created by 文恒 on 2022/4/6.
//
#include "boost/asio.hpp"

#include "chatServer.h"
#include "dateTimeMgr.h"
using namespace boost::asio;

int main()
{
//    system("chcp 65001");
    dateTimeMgr::getDateTime();
    io_service ioserver;
    ip::tcp::endpoint ed(ip::tcp::v4(), 8080);

    chatServer server(ioserver, ed);

    std::cout << "服务器开启监听:\n" << std::endl;
    server.accept_server();

    ioserver.run();

    return 0;
}