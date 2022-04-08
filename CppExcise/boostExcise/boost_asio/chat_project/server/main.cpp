//
// Created by 文恒 on 2022/4/6.
//
#include "boost/asio.hpp"

#include "chatServer.h"

using namespace boost::asio;

int main()
{
    io_service ioserver;
    ip::tcp::endpoint ed(ip::tcp::v4(), 8080);

    chatServer server(ioserver, ed);

    server.accept_server();

    ioserver.run();

    return 0;
}