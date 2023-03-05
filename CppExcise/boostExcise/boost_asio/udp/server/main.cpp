//
// Created by 文恒 on 2022/4/4.
//
#include <string>
#include <iostream>
#include "boost/asio.hpp"

using namespace boost::asio;

[[noreturn]] void handleConnect()
{
    char buf[1024];

    io_service ioService;
    ip::udp::socket sock(ioService, ip::udp::endpoint(ip::udp::v4(), 8000));

    while(true)
    {
        ip::udp::endpoint sender;
        size_t bytes = sock.receive_from(buffer(buf), sender);
        std::cout << "remote ip: " << sender.address() << std::endl;
        std::cout << "receive client msg: " << std::string (buf, bytes) << std::endl;

        std::string msg(buf, bytes);

        sock.send_to(buffer(msg), sender);
    }

}

int main()
{
    handleConnect();

    return 0;
}