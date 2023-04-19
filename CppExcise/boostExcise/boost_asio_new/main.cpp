//
// Created by wenheng on 23-3-25.
//

#include "network/network.h"
#include "netResolver/netResolver.h"
#include "boost/asio/steady_timer.hpp"

#include "thread"
#include "string"
#include "cstring"

void test()
{
    netResolver* resolver = netResolver::generator();
    char body[] = "hello linux";
    netHead head;
    head.len = sizeof(body);
    std::shared_ptr<char> data = resolver->compose(head, body, sizeof body);

    char buff[1024] = {0};
    char* ptr = data.get();
    memcpy(buff, ptr, sizeof(head) + sizeof(body) + 1);
    std::cout << "data = " << data << std::endl;
}


int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr << "arg count error" << std::endl;
        exit(-1);
    }
    std::cout << "*argv[0] = " << (argv[0]) << std::endl;
    std::cout << "*argv[1] = " << (argv[1]) << std::endl;
    u_short port = std::stoi(std::string(argv[1]));
    std::cout << "port = " << port << std::endl;
    boost::asio::io_service ioserver;

    using namespace boost::asio;
//    time_with_func timers(ioserver, 5, [](){
//       std::cout << "hello world" << std::endl;
//    });

    boost::asio::ip::tcp::endpoint  ed(tcp::v4(), port);
    std::cout << "addr = " << ed.address().to_string() << std::endl;
    network net(ioserver, ed);
    net.run();

    ioserver.run();
//    test();
    return 0;
}