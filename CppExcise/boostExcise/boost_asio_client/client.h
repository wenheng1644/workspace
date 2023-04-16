//
// Created by wenheng on 23-3-26.
//

#ifndef BOOST_ASIO_CLIENT_CLIENT_H
#define BOOST_ASIO_CLIENT_CLIENT_H

#include "boost/asio.hpp"
#include "boost/format.hpp"
#include "boost/bind.hpp"
#include "memory"

#include "../boost_asio_new/netResolver/netResolver.h"


using namespace boost::asio;
class client : public std::enable_shared_from_this<client>{
public:
    client(io_service& ioService, ip::tcp::endpoint ed) : m_socket(ioService), m_ed(ed) {}

    void connect();

private:
    ip::tcp::socket m_socket;
    ip::tcp::endpoint m_ed;
    netMsg m_msg;

    void handle_connect(boost::system::error_code ec);
    void handle_write();
    
    void handle_readhead(boost::system::error_code ec, size_t bytes);
    void handle_readbody(boost::system::error_code ec, size_t bytes);

    void handle_checkConnect();
};


#endif //BOOST_ASIO_CLIENT_CLIENT_H
