
#include "chatServer.h"
#include "boost/bind/bind.hpp"

void chatServer::accept_server()
{
    chatSessionPtr session_ptr(new chatSession(m_ioserver, m_room));

    m_acceptor.async_accept(session_ptr->sock(), boost::bind(&chatServer::handler_accept_server, this, session_ptr, boost::asio::placeholders::error));
}

//递归运行
void chatServer::handler_accept_server(chatSessionPtr session_ptr, boost::system::error_code ec)
{
    if(!ec)
        session_ptr->start();

    accept_server();
}