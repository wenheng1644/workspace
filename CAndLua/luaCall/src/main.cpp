//
// Created by �ĺ� on 2023/2/13.
//

#include "luaCall.h"
#include "string"
#include "iostream"
#include "boost/format.hpp"

int main(int argc, char* argv[])
{
//    std::cout << boost::format("argc = %d, argv[0] = %s") % argc % argv[0] << std::endl;
    luaCall* g_luaCall = luaCall::generator();
    std::string ip = g_luaCall->getLuaVarByKey("ip");
    std::string port = g_luaCall->getLuaVarByKey("port");

    std::cout << boost::format("ip = %s, port = %d") % ip % std::stod(port) << std::endl;
    return 0;
}