
#include "chatServer.h"
#include "boost/bind/bind.hpp"

#include "thread"
#include "iostream"

void chatServer::accept_server()
{

    chatSessionPtr session_ptr(new chatSession(m_ioserver, m_room));
    m_acceptor.async_accept(session_ptr->sock(), boost::bind(&chatServer::handler_accept_server, this, session_ptr, boost::asio::placeholders::error));

//    std::thread client_connect(p);

//    client_connect.join();
}

//递归运行
void chatServer::handler_accept_server(chatSessionPtr session_ptr, boost::system::error_code ec)
{
    if(!ec)
    {
//        std::cout << "当前线程id: " << std::this_thread::get_id() << std::endl
        std::thread newClient([=](){
            std::string msg("服务器连接成功~~~\n开服时间: ");
            msg += m_openServerTime;
            msg += "\n";
            chatMsg serverMsg(msg);

            session_ptr->deliver(serverMsg);
            session_ptr->start();
            std::cout << "开启连接线程: " << std::this_thread::get_id() << std::endl;
        });

        newClient.detach();
    }
    accept_server();
}