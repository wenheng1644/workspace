#include "TCP_GConnection.h"

TCP_GConnection::TCP_GConnection(ioserver_tp& io) : TCPConnection(io)
{
}

void TCP_GConnection::run()
{
    netMsg_ptr msg(new netMsg);

    size_t headlen = sizeof(netHead);

    using namespace boost::asio;
    m_sockect.async_read_some(boost::asio::buffer(&(msg->head), headlen), std::bind(&TCP_GConnection::on_handleReadHead, shared_from_this(), \
        msg, placeholders::error, placeholders::bytes_transferred));
}

void TCP_GConnection::send(netMsg_ptr& msg)
{
    std::string netStr = getSerlizeNetMsgStr(*msg);

    using namespace boost::asio;
    m_sockect.async_write_some(boost::asio::buffer(netStr, netStr.size()), std::bind(&TCP_GConnection::on_handleSend, shared_from_this(), \
        placeholders::error, placeholders::bytes_transferred));

}

address_tp TCP_GConnection::getaddr()
{
    auto ed = m_sockect.local_endpoint();
    return ed.address();
}

void TCP_GConnection::on_handleSend(ec_code_tp ec, size_t bytes)
{
    if(ec)
    {
        printf("TCP_GConnection::on_handleSend | send error.... bytes = %d\n", bytes);
        return;
    }

    printf("TCP_GConnection::on_handleSend | data send successfully~\n");
}

void TCP_GConnection::on_handleReadHead(netMsg_ptr msg, ec_code_tp ec, size_t bytes)
{
    if(ec)
    {
        std::string formatstr = getFormatStr("error content = %1%, bytes = %2%", ec.message(), bytes);
        printf("TCP_GConnection::on_handleReadHead | %s\n", formatstr.c_str());
        close();
        return;
    }

    msg->datas.resize(msg->head.len, 0);

    using namespace boost::asio;
    m_sockect.async_read_some(boost::asio::buffer(msg->datas, msg->head.len), std::bind(&TCP_GConnection::on_handleReadBody, shared_from_this(), \
        msg, placeholders::error, placeholders::bytes_transferred));

    
}

void TCP_GConnection::on_handleReadBody(netMsg_ptr msg, ec_code_tp ec, size_t bytes)
{
    if(ec)
    {
        std::string strformat = getFormatStr("error content = %1%, bytes = %2%", ec.message(), bytes);
        printf("TCP_GConnection::on_handleReadBody | %s\n", strformat.c_str());

        return;
    }

    //TO-DO网关业务
    auto p = m_target.lock();
    if(p)
        p->push_netMsg(msg);

    run();
}
