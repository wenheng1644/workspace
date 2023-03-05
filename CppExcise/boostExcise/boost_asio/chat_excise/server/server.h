//
// Created by 文恒 on 2022/4/10.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H
#include <string>
#include "mutex"
#include "condition_variable"

#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/bind/bind.hpp"

#include "msgHeader.h"
#include "chatMsg.h"

using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
typedef boost::system::error_code error_code_type;
typedef boost::shared_ptr<chatMsg> chatMsg_ptr;

class server {
public:
    server(io_service& ioserver, ip::tcp::endpoint ed) : m_ioserver(ioserver), m_acceptor(ioserver, ed) {}

    void run();
private:
    io_service& m_ioserver;
    ip::tcp::acceptor m_acceptor;

    std::mutex m_mutex;

    void handle_connect(chatMsg_ptr ptr);
    void handle_readBody(chatMsg_ptr chatMsgPtr);

};


#endif //SERVER_SERVER_H
