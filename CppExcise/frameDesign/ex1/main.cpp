#include <iostream>

#include "TCP_Server/TCP_Server.h"
#include "csignal"
//#include "QtCore/QtCore"
boost::asio::io_service g_io;
TCP_Server g_server(g_io);

void register_signal(int signal_value)
{
    std::cout << "register_signal get signal value = " << signal_value << std::endl;
    g_server.handle_close(signal_value);

}


int main(int argc, char* argv[]) {

    signal(SIGINT, register_signal);
    signal(SIGTERM, register_signal);
    if(argc != 3)
    {
        std::cerr << boost::format("参数不足两个, argc = %d") % argc << std::endl;
        return 0;
    }

    std::string process(argv[0]);
    std::string ip(argv[1]);
    u_short port = std::stoi(std::string(argv[2]));

    std::cout << boost::format("打印输入参数: [%s] = %s-%d") % process % ip % port << std::endl;

    boost::asio::ip::tcp::endpoint ed(boost::asio::ip::address::from_string(ip), port);
    g_server.init(ed);
    std::cout << "Hello, World!" << std::endl;
    g_io.run();
    return 0;
}
