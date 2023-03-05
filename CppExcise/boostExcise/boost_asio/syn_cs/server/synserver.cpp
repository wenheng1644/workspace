#include <iostream>

#include "boost/asio.hpp"

using namespace boost::asio;

int main()
{
    io_service server;
    ip::tcp::acceptor acceptor(server, ip::tcp::endpoint(ip::tcp::v4(), 7456));

    while(true)
    {
        ip::tcp::socket c_socket(server);

        acceptor.accept(c_socket);

        std::cout << "remote add:" << c_socket.remote_endpoint().address() << std::endl;

        boost::system::error_code ec;
        c_socket.write_some(buffer("ok...server connect~~"), ec);

        if(ec)
        {
            std::cout << "server broken..." << std::endl;break;
        }

        while(true)
        {
            char readbuff[100] = {};
            c_socket.read_some(buffer(readbuff));
            std::cout << "client msg: " << readbuff << std::endl;

//            if(!c_socket.available()) break;
        }
    }

    return 0;
}