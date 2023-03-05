#include <iostream>
#include <string>

#include "boost/asio.hpp"

using namespace boost::asio;

int main()
{
    io_service server;
    ip::tcp::socket c_socket(server);

    ip::tcp::endpoint ed(ip::address_v4::from_string("121.37.233.74"), 7456);
    boost::system::error_code ec;

    c_socket.connect(ed, ec);

    if(ec)
    {
        std::cout << "connect woring: " << ec.what() << std::endl;
        exit(0);
    }

    char buf[100] = {};
    c_socket.read_some(buffer(buf), ec);

    std::cout << buf << std::endl;

    std::string str;
    while(std::cin >> str || str != "q")
    {
        boost::system::error_code ec1;
        c_socket.write_some(buffer(str), ec1);
        str.clear();

    }
    return 0;
}