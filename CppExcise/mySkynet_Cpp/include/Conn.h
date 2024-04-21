//
// Created by ADMIN on 24-4-21.
//

#ifndef SUNNET_CONN_H
#define SUNNET_CONN_H
#pragma once

#include "iostream"
class Conn
{
public:
    enum TYPE{
        LISTEN = 1,
        CLIENT = 2,
    };

    u_int8_t m_type;
    int fd;
    u_int32_t m_serviceid;
};


#endif //SUNNET_CONN_H
