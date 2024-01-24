#include "TCPConnection.h"

#include "functional"
#include "boost/bind.hpp"

void TCPConnection::send(const std::vector<char> &buff)
{
    send(buff.data(), buff.size());
}

void TCPConnection::run()
{
    netMsg_ptr msg(new netMsg);
    using namespace boost::asio;
    size_t headlen = sizeof(netHead);
    m_sockect.async_read_some(boost::asio::buffer(&(msg->head), headlen), \
        boost::bind(&TCPConnection::on_handleReadHead, shared_from_this(), msg, placeholders::error, placeholders::bytes_transferred));
}

void TCPConnection::send(const char *buff, size_t len)
{
    m_sockect.async_write_some(boost::asio::buffer(buff, len),\
        boost::bind(&TCPConnection::on_handleSend, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void TCPConnection::on_handleSend(ec_code_tp ec, size_t bytes)
{
    if(ec)
    {
        printf("TCPConnection::on_handleSend | send error, bytes = %d\n", bytes);
        return;
    }
}

void TCPConnection::on_handleReadHead(netMsg_ptr msg, ec_code_tp ec, size_t bytes)
{
    if(ec)
    {
        printf("TCPConnection::on_handleRead | read data error!  bytes = %d\n", bytes);
        m_sockect.close();
        return;
    }

    msg->datas.resize(msg->head.len, 0);
    using namespace boost::asio;

    io_service::strand s(m_io);
    std::function<void()> handle = boost::bind(&TCPConnection::on_handleReadBody, shared_from_this(), msg, placeholders::error, placeholders::bytes_transferred);
    m_sockect.async_read_some(boost::asio::buffer(msg->datas, msg->head.len), \
        s.wrap(handle));
}

void TCPConnection::on_handleReadBody(netMsg_ptr msg, ec_code_tp ec, size_t bytes)
{
    if(ec)
    {
        printf("TCPConnection::on_handleReadBody | read body error!     bytes = %d\n", bytes);
        m_sockect.close();
        return;
    }

    //业务操作--ToDo 免互斥量

    run();
}
