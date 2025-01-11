//
// Created by 文恒 on 24-10-6.
//

#include <iostream>

#include "Sunnet.h"
#include "sol/sol.hpp"

int main()
{
    std::cout << "Hello MacOs!" << std::endl;

    new Sunnet();

    Sunnet::inst->Start();


    // auto srv1_id = Sunnet::inst->NewService("ping");
    // auto srv2_id = Sunnet::inst->NewService("pong");

    // Sunnet::inst->Listen(8888, srv1_id);

    sol::state lua;
    Sunnet::inst->Wait();


    // tcp::socket s(Sunnet::inst->m_io_service);
    // s.native_handle();
    return 0;
}