#include "TCPConnection.h"

#include "functional"
#include "boost/bind.hpp"

void TCPConnection::send(std::vector<char> &buff)
{

    m_sockect.async_write_some(boost::asio::buffer(buff), \
        boost::bind(&TCPConnection::on_handleSend, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void TCPConnection::run()
{

}

void TCPConnection::on_handleSend(ec_code_tp ec, size_t bytes)
{
    if(ec)
    {
        printf("TCPConnection::on_handleSend | send error, bytes = %d\n", bytes);
        return;
    }
}

void TCPConnection::on_handleReadHead(ec_code_tp ec, size_t bytes)
{
    if(ec)
    {
        printf("TCPConnection::on_handleRead | read data error!  bytes = %d\n", bytes);
        return;
    }

    run();
}
