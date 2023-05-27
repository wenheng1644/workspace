//
// Created by wenheng on 23-3-26.
//

#include "client.h"

int main()
{
    using namespace boost::asio;

    std::string name;
    std::cout << "enter your name:";
    while(std::getline(std::cin, name))
    {
        if(!name.empty() && name.size() < 20)
            break;
        std::cout << "please enter right name:";
    }
    std::cout << "your name: " << name << std::endl;

    io_service ioService;
    io_service::work w(ioService);
    ip::tcp::endpoint ed(ip::tcp::v4(), 8888);
    client c(ioService, ed, name);

    c.connect();

    ioService.run();

    return 0;
}