//
// Created by 文恒 on 2022/4/4.
//
#include <iostream>
#include <string>

#include "boost/asio.hpp"

using namespace boost::asio;

void syn_echo()
{
    io_service ioService;
    ip::udp::socket sock(ioService, ip::udp::endpoint(ip::udp::v4(), 0));

    ip::udp::endpoint ep(ip::address_v4::from_string("127.0.0.1"), 8000);

    std::string msg("hey server");

    sock.send_to(buffer(msg), ep);

//    sock.send_to(buffer("hello server"), ep);
//    std::string get(buff, bytes);
    char buff[100];
    sock.receive_from(buffer(buff), ep);
    std::cout << "get msg: " << buff << std::endl;

    sock.close();
}

int main()
{
//    while(true)
    syn_echo();

    return 0;
}