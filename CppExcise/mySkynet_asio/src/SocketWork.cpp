//
// Created by 文恒 on 24-10-8.
//

#include "SocketWork.h"

#include <iostream>
#include <Sunnet.h>
#include <unistd.h>
#include <functional>

void SocketWork::Init()
{
    std::cout<<"SocketWork::Init()"<<std::endl;
}

void SocketWork::operator()()
{
    std::cout << "Socket work start" << std::endl;
    boost::asio::io_service::work w(Sunnet::inst->m_io_service);

    Sunnet::inst->m_io_service.run();
    std::cout << "Socket work end" << std::endl;
}

void SocketWork::run(std::shared_ptr<tcp::acceptor> ac, u_int32_t srvid)
{
    std::cout << "SocketWork::run: threadid = " << std::this_thread::get_id() << std::endl;
    std::shared_ptr<Conn> conn = std::make_shared<Conn>(Sunnet::inst->m_io_service);
    ac->async_accept(conn->socket(), std::bind(&SocketWork::OnAccept, this, conn, srvid, ac, boost::asio::placeholders::error));
}

void SocketWork::OnAccept(std::shared_ptr<Conn> conn, u_int32_t srvid, std::shared_ptr<tcp::acceptor> ac, boost::system::error_code ec)
{
    if(ec)
    {
        std::cerr << "Socket work error: " << ec.message() << std::endl;
        return;
    }

    if(!ac || !ac->is_open())
    {
        std::cerr << "Socket work error: " << ec.message() << std::endl;
        return;
    }
    std::cout << "SocketWork::OnAccept: threadid = " << std::this_thread::get_id() << std::endl;
    std::cout<<"SocketWork::OnAccept: conn->srvid = " << conn->m_server_id << ", srvid = " << srvid << std::endl;

    run(ac, srvid);
    Sunnet::inst->AddConn(conn, srvid, Conn::CLIENT);
    conn->run();

    std::shared_ptr<SocketAcceptMsg> msg = std::make_shared<SocketAcceptMsg>();
    msg->m_type = BaseMsg::TYPE::SOCKET_ACCEPT;
    msg->m_socket_uuid = conn->m_uuid;
    
    Sunnet::inst->Send(srvid, msg);
}

