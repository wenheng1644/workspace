//
// Created by 文恒 on 2022/4/3.
//

#include "asynServer.h"

int main()
{
    io_service ioserver;
    asynServer asynServer(ioserver);

    asynServer.start();

    ioserver.run();

    return 0;
}
