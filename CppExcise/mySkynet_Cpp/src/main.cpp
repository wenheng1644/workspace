//
// Created by ADMIN on 24-4-16.
//

#include "iostream"

#include "Sunnet.h"

void test()
{
    auto type = std::make_shared<std::string>("ping");
    u_int32_t ping1 = Sunnet::inst->NewService(type);
    u_int32_t ping2 = Sunnet::inst->NewService(type);
    u_int32_t ping3 = Sunnet::inst->NewService(type);

    auto msg1 = Sunnet::MakeMsg(ping1, new char[3]{'h', 'i', '\0'}, 3);
    auto msg2 = Sunnet::MakeMsg(ping1, new char[6]{'h', 'e', 'l','l','o', '\0'}, 6);

    Sunnet::inst->Send(ping2, msg1);
    Sunnet::inst->Send(ping3,msg2);
}

int main()
{
    new Sunnet();

    Sunnet::inst->Start();

    test();
    Sunnet::inst->Wait();
    return 0;
}