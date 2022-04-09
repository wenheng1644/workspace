//
// Created by 文恒 on 2022/4/9.
//

#include "server.hpp"

#include "boost/asio.hpp"

int main()
{
    io_service ioserver;
    ip::tcp::endpoint ed(ip::tcp::v4(), 8000);

    chatServer server(ioserver, ed);

    server.run();

    ioserver.run();

    return 0;
}
