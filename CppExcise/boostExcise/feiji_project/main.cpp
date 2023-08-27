//
// Created by wenheng on 23-6-20.
//

#include "iostream"
#include "boost/asio.hpp"
#include "boost/format.hpp"

#include "cmd.h"
#include "playerInfo_cmd.h"

#include "netserver.h"


int main(int argc, char* argv[])
{
    std::cout << "项目入口" << std::endl;
    if(argc != 2)
    {
        std::cout << boost::format("参数不足 num = %d") % argc << std::endl;
        return -1;
    }

    u_short port = std::stoi(argv[1]);
//    playerInfoCmdRes cmd(nullptr);

//    printf("id = %d, subid = %d, value = %d\n", cmd.id, cmd.subid, cmd.value);
    boost::asio::io_service io;
    boost::asio::ip::tcp::endpoint ed(tcp::v4(), port);
    netserver svr(io, ed);

    svr.run();

    io.run();
    return 0;
}