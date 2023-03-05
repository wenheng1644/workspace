//
// Created by нд╨Ц on 2022/5/14.
//

#ifndef SERVER_MSGHEADER_H
#define SERVER_MSGHEADER_H

#include "iostream"

struct msgHeader
{
    uint32_t    bodySize;
    uint8_t     sysId;
    uint8_t     pid;
};

#endif //SERVER_MSGHEADER_H

