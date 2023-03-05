//
// Created by нд╨Ц on 2022/7/12.
//

#ifndef BASEEXCISE_MYWINSOCK_H
#define BASEEXCISE_MYWINSOCK_H

#include "windows.h"
#include "winsock2.h"

namespace myWinSock
{
    void set_sockstate();
    void clean_exit();

    void start();

    void gethostInfo();
}

#endif //BASEEXCISE_MYWINSOCK_H
