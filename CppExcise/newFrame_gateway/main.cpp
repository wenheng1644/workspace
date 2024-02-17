#include "iostream"

#include "comm/GateManager.h"
#include "TCP_gateway/TCP_GServer.h"

int main(int argc, char* argv[])
{

    printf("hello world\n");
    GateManager::getObj()->init();
    GateManager::getObj()->run();

    ioserver_tp io;
    address_tp add = address_tp::from_string("192.168.31.145");
    TCP_GServer ser(io, add, 8888);

    ser.run();

    io.run();
    return 0;
}