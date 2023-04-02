//
// Created by wenheng on 23-3-26.
//

#include "client.h"

int main()
{
    using namespace boost::asio;
    io_service ioService;
    io_service::work w(ioService);
    ip::tcp::endpoint ed(ip::tcp::v4(), 8888);
    client c(ioService, ed);

    c.connect();

    ioService.run();

    return 0;
}