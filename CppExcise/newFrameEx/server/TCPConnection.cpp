#include "TCPConnection.h"

#include "functional"
#include "boost/bind/bind.hpp"
#include "boost/function.hpp"
#include "thread"

#include "../comm/resourceManager.h"


void TCPConnection::send(const std::vector<char> &buff)
{
    send(buff.data(), buff.size());
}

void TCPConnection::send(netMsg_ptr &msg)
{
    std::string str = getSerlizeNetMsgStr(*msg);
    printf("TCPConnection::send | 发送数据....\n");
    send(str.data(), str.size());
}

void TCPConnection::run()
{
    // netMsg_ptr msg(new netMsg);
    // netStrMsg_ptr netStr(new netStrMsg);
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
    std::string formatstr = getFormatStr(" onlyid = %1%, pre addr = %2%, pre port = %3%, headlen = %4%, threadId = %5%", m_onlyid, ed.address().to_string(), ed.port(), headlen, std::this_thread::get_id());
    printf("TCPConnection::run | threadSize = %d, %s\n", threadSize, formatstr.c_str());
    // netStr->headStr.resize(headlen, 0);

    ioserver_tp::strand s(m_io);
    auto handle = std::bind(&TCPConnection::on_handleReadHead, shared_from_this(), msg, placeholders::error, placeholders::bytes_transferred);
    // std::function<void()> handle = std::bind(&TCPConnection::on_handleReadHead, shared_from_this(), msg, placeholders::error, placeholders::bytes_transferred);
    m_sockect.async_read_some(boost::asio::buffer((char*)&msg->head, headlen), \
        s.wrap(handle));
}

void TCPConnection::send(const char *buff, size_t len)
{
    std::string formatStr = getFormatStr("执行异步发送, bytes len = %1%, threadId = %2%", (int)len, std::this_thread::get_id());
    printf("TCPConnection::send | %s\n", formatStr.c_str());
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
    std::string formatStr = getFormatStr("成功发送bytes = %1%, threadId = %2%", (int)bytes, std::this_thread::get_id());
    printf("TCPConnection::on_handleSend | %s\n", formatStr.c_str());
}

void TCPConnection::on_handleReadHead(netMsg_ptr msg, ec_code_tp ec, size_t bytes)
{
    if(ec)
    {
        printf("TCPConnection::on_handleRead | read data error!  bytes = %d\n", bytes);
        m_sockect.close();
        return;
    }

    netHead head = msg->head;
    msg->datas.resize(head.len, 0);
    using namespace boost::asio;

    io_service::strand s(m_io);

    auto handle = boost::bind(&TCPConnection::on_handleReadBody, shared_from_this(), msg, placeholders::error, placeholders::bytes_transferred);

    // printf("the handle type = %s\n", typeid(handle).name());
    std::string formatStr = getFormatStr("type = %1%, subtype = %2%, len = %3%, version = %4%, sendtime = %5%, checkcode = %6%, threadId = %7%", \
        (int)head.type, (int)head.subtype, (int)head.len, (int)head.version, head.sendtime, (int)head.checkcode, std::this_thread::get_id());
    printf("TCPConnection::on_handleReadHead recv(%d)| %s\n", bytes,  formatStr.c_str());
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

    netHead head = msg->head;
    std::string formatStr = getFormatStr("收到的数据打印 : type = %1%, subtype = %2%, bodylen = %3%, threadId = %4%", (int)head.type, (int)head.subtype, (int)head.len, std::this_thread::get_id());

    printf("TCPConnection::on_handleReadBody  | %s\n", formatStr.c_str());
    cmd::chatMessageCmd content = parseSerlizeStr<cmd::chatMessageCmd>(msg->datas);

    printf("TCPConnection::on_handleReadBody | status = %d, content = %s\n", content.status(), content.content().c_str());

    send(msg);
    //业务操作--ToDo 免互斥量
    run();
}
