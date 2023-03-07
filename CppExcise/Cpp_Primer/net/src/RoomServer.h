#ifndef ROOMSERVER
#define ROOMSERVER
#include "net.h"

class roomServer
{
public:
    roomServer(const std::string& ip, u_short port);

    bool start();

private:


    void transfer_msg();
};

#endif