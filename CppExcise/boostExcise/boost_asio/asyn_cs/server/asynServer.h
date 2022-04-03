#ifndef ASYNSERVER
#define ASYNSERVER

#include <string>
#include <iostream>

#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/smart_ptr.hpp"
using namespace boost::asio;

class asynServer
{
public:
    asynServer(io_service& ioserver) : m_ioserver(ioserver), m_acceptor(ioserver, ip::tcp::endpoint(ip::address_v4(), 7456)) {}

    void start();

private:
    io_service& m_ioserver;
    ip::tcp::acceptor m_acceptor;

    void connect_callback(boost::shared_ptr<ip::tcp::socket> psocket, boost::system::error_code ec);
    void sendMsg_callback(boost::system::error_code ec, size_t bytes);    
};



#endif