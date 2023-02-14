//
// Created by нд╨Ц on 2023/2/13.
//

#include "luaCall.h"
#include "string"
#include "iostream"
#include "boost/format.hpp"

int main(void)
{
    luaCall* g_luaCall = luaCall::generator();
    std::string ip = g_luaCall->getLuaVarByKey("ip");
    std::string port = g_luaCall->getLuaVarByKey("port");

    std::cout << boost::format("ip = %s, port = %d") % ip % std::stod(port) << std::endl;
    return 0;
}