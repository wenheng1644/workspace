//
// Created by 文恒 on 2022/4/10.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include "boost/asio.hpp"
#include "boost/bind/bind.hpp"

#include <string>

#include "../server/msgHeader.h"

using namespace boost::asio;

typedef boost::system::error_code error_code_type;

class client {
public:
    client(io_service& ioserver) : m_ioserver(ioserver), m_socket(ioserver) {}

    void run();

private:
    io_service& m_ioserver;
    ip::tcp::socket m_socket;
    std::string m_readMsg;

    void handler_connect(const error_code_type& ec);

    void write(std::string& data);
};


#endif //CLIENT_CLIENT_H
