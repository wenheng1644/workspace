//
// Created by wenheng on 23年9月23日.
//

#ifndef EX1_TCP_SERVER_H
#define EX1_TCP_SERVER_H

#include "boost/asio.hpp"
#include "../common/threadSafe_Container.h"

#include "Session.h"

using namespace boost::asio;

class TCP_Server{
//    class Session;
public:
    TCP_Server(io_service& io, ip::tcp::endpoint ed) : m_io(io), m_acceptor(io, ed) {}
    TCP_Server(io_service& io) : m_io(io), m_acceptor(io, ip::tcp::endpoint()) {}

    void init(ip::tcp::endpoint ed);

    void handle_close(int signalvalue);
    ~TCP_Server();
private:
    io_service& m_io;
    ip::tcp::acceptor m_acceptor;

//    threadSafe_Container<Session> m_Sessions_;
//    threadSafe_Container<Session> m_WaitConnectSessions;
    void run();

    void handle_accept(SessionPtr session, error_code_type ec);

};


#endif //EX1_TCP_SERVER_H
