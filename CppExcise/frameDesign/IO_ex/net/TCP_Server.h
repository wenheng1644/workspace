//
// Created by wenheng on 23年12月9日.
//

#ifndef IO_EX_TCP_SERVER_H
#define IO_EX_TCP_SERVER_H

#include "boost/asio.hpp"
#include "boost/noncopyable.hpp"

class TCP_Server : boost::noncopyable {
    using ioserver_type = boost::asio::io_service;
    using TCP = boost::asio::ip::tcp;
public:
    TCP_Server(ioserver_type& io, TCP::endpoint ed);


private:
    ioserver_type& m_io;
    TCP::acceptor m_acceptor;


    void run();

    void handle_accpet();
};


#endif //IO_EX_TCP_SERVER_H
