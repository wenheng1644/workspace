//
// Created by wenheng on 23-3-26.
//

#ifndef BOOST_ASIO_CLIENT_CLIENT_H
#define BOOST_ASIO_CLIENT_CLIENT_H

#include "boost/asio.hpp"
#include "boost/format.hpp"

#include "../boost_asio_new/netResolver/netResolver.h"


using namespace boost::asio;
class client {
public:
    client(io_service& ioService, ip::tcp::endpoint ed) : m_socket(ioService), m_ed(ed) {}

    void connect();

private:
    ip::tcp::socket m_socket;
    ip::tcp::endpoint m_ed;
    char m_buf[1024];

    void handle_read();
    void handle_write();

    static std::mutex s_mutex;
};


#endif //BOOST_ASIO_CLIENT_CLIENT_H
