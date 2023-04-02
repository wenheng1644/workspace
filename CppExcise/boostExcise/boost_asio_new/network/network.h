//
// Created by wenheng on 23-3-25.
//

#ifndef BOOST_ASIO_NEW_NETWORK_H
#define BOOST_ASIO_NEW_NETWORK_H

#define BYTESLEN 1024

#include "iostream"
#include "string"
#include "memory"

#include "boost/format.hpp"
#include "boost/asio.hpp"
//#include
#include "functional"
#include "binders.h"
#include "boost/bind/bind.hpp"
#include "boost/chrono.hpp"
#include "boost/chrono/chrono.hpp"

#include "../netResolver/netResolver.h"

using namespace boost::asio::ip;
class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket) : m_sessionSocket(std::move(socket)) {}

    void start() {read();}

private:
    tcp::socket m_sessionSocket;
    std::array<char, BYTESLEN> m_data;

    void read();
    void write(size_t len);
};

class network {
public:
    network(boost::asio::io_service&  ioserver, tcp::endpoint ed): m_acceptor(ioserver, ed) \
     , m_socket(ioserver) {}

    void run();
private:
    tcp::socket m_socket;
    tcp::acceptor m_acceptor;
};


class time_with_func
{
    typedef void(handlder_type)(boost::system::error_code ec);

public:
    time_with_func(boost::asio::io_service& ioService, int maxCnt, void(func)()) : m_cnt(0), m_maxCnt(maxCnt)\
    , m_func(func), m_timer(ioService, std::chrono::seconds(1))
    {
        m_timer.async_wait(boost::bind(&time_with_func::handler, this, boost::asio::placeholders::error));
    }

private:

    int m_cnt;
    int m_maxCnt;
    std::function<void()> m_func;
    boost::asio::steady_timer m_timer;

    void handler(const boost::system::error_code&)
    {
        if(m_cnt++ > m_maxCnt) return;

        m_func();

        m_timer.expires_from_now(std::chrono::seconds(1));

        m_timer.async_wait(boost::bind(&time_with_func::handler, this, boost::asio::placeholders::error));
    }

};

#endif //BOOST_ASIO_NEW_NETWORK_H
