#include "TCPConnection.h"

#include "functional"
#include "boost/bind/bind.hpp"
#include "boost/function.hpp"

#include "../comm/resourceManager.h"


void TCPConnection::send(const std::vector<char> &buff)
{
    send(buff.data(), buff.size());
}

void TCPConnection::send(const netMsg_ptr &msg)
{
    std::string str = getSerlizeNetMsgStr(*msg);

    send(str.data(), str.size());
}

void TCPConnection::run()
{
    netMsg_ptr msg(new netMsg);
    using namespace boost::asio;
    size_t headlen = sizeof(netHead);

    ec_code_tp ec;
    auto ed = m_sockect.remote_endpoint(ec);
    if(ec)
    {
        printf("TCPConnection::run | 无法拿到对端数据.....\n");
        return;
    }
    size_t threadSize = ResourceManager::getObj()->get_ioThreadSize();
    std::string formatstr = getFormatStr(" onlyid = %1%, pre addr = %2%, pre port = %3%", m_onlyid, ed.address().to_string(), ed.port());
    printf("TCPConnection::run | threadSize = %d, %s\n", threadSize, formatstr.c_str());

    ioserver_tp::strand s(m_io);
    auto handle = std::bind(&TCPConnection::on_handleReadHead, shared_from_this(), msg, placeholders::error, placeholders::bytes_transferred);
    // std::function<void()> handle = std::bind(&TCPConnection::on_handleReadHead, shared_from_this(), msg, placeholders::error, placeholders::bytes_transferred);
    m_sockect.async_read_some(boost::asio::buffer((char*)&(msg->head), headlen), \
        s.wrap(handle));
}

void TCPConnection::send(const char *buff, size_t len)
{
    m_sockect.async_write_some(boost::asio::buffer(buff, len),\
        std::bind(&TCPConnection::on_handleSend, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
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

    auto handle = boost::bind(&TCPConnection::on_handleReadBody, shared_from_this(), msg, placeholders::error, placeholders::bytes_transferred);

    printf("the handle type = %s\n", typeid(handle).name());
    m_sockect.async_read_some(boost::asio::buffer(msg->datas, msg->head.len), \
        s.wrap(handle));
}

void TCPConnection::on_handleReadBody(netMsg_ptr msg, ec_code_tp ec, size_t bytes)
{
    if(ec)
    {
        printf("TCPConnection::on_handleReadBody | read body error! bytes = %d\n", bytes);
        m_sockect.close();
        return;
    }

    //业务操作--ToDo 免互斥量
    std::string formatStr = getFormatStr("收到的数据打印 : type = %d, subtype = %d, bodylen = %d\n", msg->head.type, msg->head.subtype, msg->head.len);
    run();
}
