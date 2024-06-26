
#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"

#include "chatRoom.h"
#include "chatSession.h"                

using namespace boost::asio;

typedef boost::shared_ptr<chatSession> chatSessionPtr;

class chatServer
{
private:
    io_service& m_ioserver;
    chatRoom m_room;
    ip::tcp::acceptor m_acceptor;

    std::string m_openServerTime;

    void handler_accept_server(chatSessionPtr session_ptr, boost::system::error_code ec);
public:
    chatServer(io_service& ioserver, ip::tcp::endpoint& ed) : m_ioserver(ioserver), m_acceptor(ioserver, ed) {}
    ~chatServer() {}

    void accept_server();

    void setOpenServerTime(const std::string serverTime)
    {
        m_openServerTime = serverTime;
    }


};




#endif