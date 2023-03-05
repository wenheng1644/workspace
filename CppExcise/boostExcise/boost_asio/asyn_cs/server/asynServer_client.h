//
// Created by 文恒 on 2022/4/3.
//

#ifndef SERVER_ASYNSERVER_CLIENT_H
#define SERVER_ASYNSERVER_CLIENT_H

#include "boost/asio.hpp"

using namespace boost::asio;

class asynServer_client {
public:
    asynServer_client(io_service& ioserver) : m_ioserver(ioserver) {}

    void start();
private:
    io_service& m_ioserver;
};


#endif //SERVER_ASYNSERVER_CLIENT_H
