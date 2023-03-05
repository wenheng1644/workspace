//
// Created by 文恒 on 2022/4/4.
//
#include <iostream>
#include <string>

#include "boost/bind/bind.hpp"
#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"

using namespace boost::asio;
using namespace boost::placeholders;
void connect_callback(boost::shared_ptr<ip::tcp::socket> psocket, boost::system::error_code ec)
{
    if(ec)
    {
        std::cout << "connect error..." << std::endl;
        return;
    }
    char readbuff[100];
    boost::system::error_code ec2;
    size_t bytes = psocket->read_some(buffer(readbuff), ec2);

    if(ec2)
    {
        std::cout << "data read error" << std::endl;
        return;
    }

    std::string msg(readbuff, bytes);
    std::cout << "client connect successful~~" << std::endl;
    std::cout << "server address: " << psocket->remote_endpoint().address().to_string() << std::endl;
    std::cout << "server data: " << msg << std::endl;
}

void read_callback(char readbuf[], boost::system::error_code ec)
{
    if(ec)
    {
        std::cout << "error~~" << std::endl;
        exit(0);
    }
    std::cout << "from server: " << readbuf << std::endl;
}

int main()
{
    io_service ioserver;
    ip::tcp::endpoint ed(ip::address::from_string("121.37.233.74"), 7456);
//    ip::tcp::socket socket(ioserver);

    boost::shared_ptr<ip::tcp::socket> psocket(new ip::tcp::socket(ioserver));

//    boost::system::error_code ec;

    psocket->async_connect(ed, boost::bind(&connect_callback, psocket, _1));

//    if(ec)
//    {
//        std::cout << "error..." << std::endl;
//        exit(0);
//    }

//    char readbuf[100] = {};
//
//    boost::system::error_code ec;
//    socket.async_(buffer(readbuf), boost::bind(&read_callback,readbuf, _1));

    ioserver.run();
    return 0;
}
