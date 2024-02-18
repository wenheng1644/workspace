#include "TCP_LogicConnection.h"

TCP_LogicConnection::TCP_LogicConnection(ioserver_tp &io) : TCPConnection(io)
{
}

void TCP_LogicConnection::run()
{
    netMsg_ptr msg(new netMsg);

    size_t headlen = sizeof(netHead);

    using namespace boost::asio;
    m_sockect.async_read_some(boost::asio::buffer(&(msg->head), headlen), std::bind(&TCP_LogicConnection::on_handleReadHead, shared_from_this(), \
        msg, placeholders::error, placeholders::bytes_transferred));
}

void TCP_LogicConnection::send(netMsg_ptr &msg)
{
    std::string sendNetStr = getSerlizeNetMsgStr(*msg);
    m_sockect.async_write_some(boost::asio::buffer(sendNetStr, sendNetStr.size()), std::bind(&TCP_LogicConnection::on_handleSend, shared_from_this(), \
        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void TCP_LogicConnection::connect(address_tp &add, u_short port)
{
    endpoint_tp ed(add, port);
    printf("TCP_LogicConnection::connect | 连接逻辑服测试...\n");
    m_sockect.async_connect(ed, std::bind(&TCP_LogicConnection::on_handleConnection, shared_from_this(), boost::asio::placeholders::error));
}

void TCP_LogicConnection::on_handleSend(ec_code_tp ec, size_t bytes)
{
    if(ec)
    {
        printf("TCP_LogicConnection::on_handleSend | 逻辑服发送数据失败 bytes = %d\n", bytes);
        close();
        return;
    }
    printf("TCP_LogicConnection::on_handleSend | 逻辑服发送数据成功 bytes = %d\n", bytes);
}

void TCP_LogicConnection::on_handleReadHead(netMsg_ptr msg, ec_code_tp ec, size_t bytes)
{
    if(ec)
    {
        std::string formatStr = getFormatStr("error content = %1%, bytes = %2%", ec.message(), bytes);
        printf("TCP_LogicConnection::on_handleReadHead | 逻辑服掉线 %s\n", formatStr.c_str());
        // close();

        auto p = m_target.lock();
        if(p)
        {
            p->close();

            printf("TCP_LogicConnection::on_handleReadHead | 用户close()\n");
        }
        else
        {
            printf("TCP_LogicConnection::on_handleReadHead | 用户指向已失效\n");
        }

        return;
    }

    size_t len = msg->head.len;
    msg->datas.resize(len, 0);

    using namespace boost::asio;
    m_sockect.async_read_some(boost::asio::buffer(msg->datas, len), std::bind(&TCP_LogicConnection::on_handleReadBody, shared_from_this(), \
        msg, placeholders::error, placeholders::bytes_transferred));
}

void TCP_LogicConnection::on_handleReadBody(netMsg_ptr msg, ec_code_tp ec, size_t bytes)
{
    if(ec)
    {
        std::string formatstr = getFormatStr("error content = %1%, bytes = %2%", ec.message(), bytes);
        printf("TCP_LogicConnection::on_handleReadBody | 逻辑服接收body失败  %s\n", formatstr.c_str());
        close();

        return;
    }

    //TO-DO  处理逻辑服数据
    auto p = m_target.lock();
    if(p)
        p->push_netLogicMsg(msg);
    
    run();
}

void TCP_LogicConnection::on_handleConnection(ec_code_tp ec)
{
    if(ec)
    {
        printf("TCP_LogicConnection::on_handleConnection | 逻辑服连接失败...\n");
        close();
        return;
    }

    printf("TCP_LogicConnection::on_handleConnection | 逻辑服连接成功!!!!\n");

    run();
}
