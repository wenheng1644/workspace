#include "chatSession.h"
#include "boost/bind/bind.hpp"

#include <iostream>

void chatSession::start()
{
    m_pRoom.join(shared_from_this());

    boost::asio::async_read(m_sock, buffer(m_readingChatMsg.getData(), HEADER_LEN), boost::bind(&chatSession::handler_readhead, shared_from_this(), boost::asio::placeholders::error));
}

void chatSession::handler_readhead(const error_code_type &ec)
{
    if(ec)
    {
        std::cerr << "数据读取错误" << std::endl;
        m_pRoom.leave(shared_from_this());
        return;
    }

    if(!m_readingChatMsg.decode())
    {
        std::cerr << "解码失败..." << std::endl;
//        m_pRoom.leave()
        return;
    }

    boost::asio::async_read(m_sock, buffer(m_readingChatMsg.body(), m_readingChatMsg.bodyLen()),
                            boost::bind(&chatSession::handler_readbody, shared_from_this(), placeholders::error));
}

void chatSession::handler_readbody(const error_code_type &ec)
{
    if(ec)
    {
        std::cerr << "读取消息体数据失败" << std::endl;
        return;
    }

    std::cout << "reback client msg: " << m_readingChatMsg.body() << std::endl;
    memset(m_readingChatMsg.getData(), 0, HEADER_LEN + BODY_LEN);

    boost::asio::async_read(m_sock, buffer(m_readingChatMsg.getData(), HEADER_LEN),
                            boost::bind(&chatSession::handler_readbody, shared_from_this(), placeholders::error));
}

void chatSession::deliver(chatMsg& msg)
{
    bool writeDone = m_wirteMsg.empty();
    m_wirteMsg.push_back(msg);

    if(writeDone)
    {
        boost::asio::async_write(m_sock, buffer(m_wirteMsg.front().getData(), m_wirteMsg.front().getLen()),
            boost::bind(&chatSession::handler_write, shared_from_this(), boost::asio::placeholders::error));
    }
    else
    {
        m_pRoom.leave(shared_from_this());
    }

}

void chatSession::handler_write(const error_code_type &ec)
{
    if(ec)
    {
        std::cerr << "发送数据错误..." << std::endl;
        return;
    }
    m_wirteMsg.pop_front();
    boost::asio::async_write(m_sock, buffer(m_wirteMsg.front().body(), m_wirteMsg.front().bodyLen()),
                             boost::bind(&chatSession::handler_write, shared_from_this(), placeholders::error));
}
