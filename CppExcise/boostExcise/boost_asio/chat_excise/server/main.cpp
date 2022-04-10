//
// Created by 文恒 on 2022/4/10.
//

#include "server.h"

#include "boost/asio.hpp"

using namespace boost::asio;

int main()
{
    io_service ioserver;
    ip::tcp::endpoint ed(ip::tcp::v4(), 8001);

    server chatServer(ioserver, ed);

    chatServer.run();

    ioserver.run();

    return 0;
}
