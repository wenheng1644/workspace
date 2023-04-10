//
// Created by wenheng on 23-3-25.
//

#ifndef BOOST_ASIO_NEW_NETWORK_H
#define BOOST_ASIO_NEW_NETWORK_H

#define BYTESLEN 1024

#include "iostream"
#include "string"
#include "memory"
#include "queue"
#include "set"

#include "boost/format.hpp"
#include "boost/asio.hpp"
//#include
#include "functional"
#include "binders.h"
#include "boost/bind/bind.hpp"
#include "boost/chrono.hpp"
#include "boost/chrono/chrono.hpp"

#include "../netResolver/netResolver.h"
#include "../netMsg/netMsg.h"
#include "../chat/chatRoom.h"

//typedef boost::system::error_code error_code_type;
//
//class Room;
//using namespace boost::asio::ip;
//class Session : public std::enable_shared_from_this<Session>
//{
//public:
//    Session(boost::asio::io_service& ioserver, Room& room) : m_sessionSocket(ioserver), m_Room(room) {}
//
//    void start();
//
//    void deliver(netMsg& msg);
//
//    tcp::socket& socket() { return m_sessionSocket;}
//private:
//    tcp::socket m_sessionSocket;
//    netMsg m_msg;
//    Room& m_Room;
//
//
//    void handle_readhead(error_code_type ec, size_t bytes);
//    void handle_readbody(error_code_type ec);
//    void handle_write(error_code_type ec);
//};
//
//typedef std::set<std::shared_ptr<Session>>  SessionQueue;
//typedef std::deque<std::shared_ptr<netMsg>> netMsgQueue;
//class Room
//{
//public:
//    Room() = default;
//    void deliver(netMsg& msg);
//    void join(std::shared_ptr<Session> session);
//    void leave(std::shared_ptr<Session> session);
//private:
//    SessionQueue m_Sessionqueue;
//    netMsgQueue m_Msgqueue;
//};

class network {
public:
    network(boost::asio::io_service&  ioserver, tcp::endpoint ed): m_acceptor(ioserver, ed) \
     , m_ioserver(ioserver) {}

    void run();
private:
    boost::asio::io_service& m_ioserver;
    tcp::acceptor m_acceptor;
    chatRoom m_Room;

    void handle_accept(chatSessionPtr session, error_code_type ec);
};


class time_with_func
{
    typedef void(handlder_type)(error_code_type ec);

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
