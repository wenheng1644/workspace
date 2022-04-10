//
// Created by 文恒 on 2022/4/10.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
#include <string>

#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/bind/bind.hpp"

using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
typedef boost::system::error_code error_code_type;

class server {
public:
    server(io_service& ioserver, ip::tcp::endpoint& ed) : m_ioserver(ioserver), m_acceptor(ioserver, ed) {}

    void run();
private:
    io_service& m_ioserver;
    ip::tcp::acceptor m_acceptor;
    std::string m_buf;


    void handler_connect(const error_code_type& ec, socket_ptr& p_socket);
    void handler_write(error_code_type ec, socket_ptr& p_socket);
    void handler_read(error_code_type ec, size_t bytes);
};


#endif //SERVER_SERVER_H
