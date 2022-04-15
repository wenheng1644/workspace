
#include "chatServer.h"
#include "boost/bind/bind.hpp"

#include "thread"

void chatServer::accept_server()
{

    auto p = [this](){
        chatSessionPtr session_ptr(new chatSession(m_ioserver, m_room));
        m_acceptor.async_accept(session_ptr->sock(), boost::bind(&chatServer::handler_accept_server, this, session_ptr, boost::asio::placeholders::error));
    };

    std::thread client_connect(p);

    client_connect.join();
}

//递归运行
void chatServer::handler_accept_server(chatSessionPtr session_ptr, boost::system::error_code ec)
{
    if(!ec)
    {
//        std::cout << "当前线程id: " << std::this_thread::get_id() << std::endl
        session_ptr->start();
    }
    accept_server();
}