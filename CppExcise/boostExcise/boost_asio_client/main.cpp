//
// Created by wenheng on 23-3-26.
//

#include "client.h"
#include "vector"


void test_mulclient()
{
    io_service ioService;
    io_service::work w(ioService);
    ip::tcp::endpoint ed(boost::asio::ip::address::from_string("192.168.31.145"), 8888);
//    client c(ioService, ed, name);
    std::vector<client> vec;

    std::string name = "xwz";
    for(int i = 0; i < 1; i++)
    {
//        client c(ioService, ed, name + std::to_string(i + 1));
        vec.push_back(client(ioService, ed, name + std::to_string(i + 1)));
    }

    for(auto& c : vec)
    {
        c.connect();
    }

    ioService.run();
}

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
    ip::tcp::endpoint ed(boost::asio::ip::address::from_string("192.168.31.145"), 8888);
    client c(ioService, ed, name);

    c.connect();

    ioService.run();

//    test_mulclient();

    return 0;
}