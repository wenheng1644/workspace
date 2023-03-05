//
// Created by 文恒 on 2022/4/10.
//

#include "client.h"

#include "boost/asio.hpp"
using namespace boost::asio;

int main()
{
    io_service ioserver;

    client cl(ioserver);

    cl.run();

    ioserver.run();

    return 0;
}