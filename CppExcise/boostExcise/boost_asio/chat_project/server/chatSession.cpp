#include "chatSession.h"
#include "boost\bind\bind.hpp"

#include <iostream>

void chatSession::start()
{
    m_pRoom.join(shared_from_this());

    boost::asio::async_read(m_sock, buffer(m_chatMsg.getData(), m_chatMsg.getLen()), boost::bind(&chatSession::handler_read, shared_from_this(), boost::asio::placeholders::error));
}

void chatSession::handler_read(boost::system::error_code ec)
{
    if(ec)
    {
        std::cerr << "数据读取错误" << std::endl;
        m_pRoom.leave(shared_from_this());
    }
}

void chatSession::handler_write(boost::system::error_code ec)
{
    if(ec)
    {
        std::cerr << "数据写入错误" << std::endl;
        return;
    }

    if(!m_wirteMsg.empty())
    {
        boost::asio::async_write(m_sock, buffer(m_wirteMsg.front().getData(), m_wirteMsg.front().getLen()),
            boost::bind(&chatSession::handler_write, shared_from_this(), boost::asio::placeholders::error));

        m_wirteMsg.pop_front(); //写完一个消息则弹出
    }
}

void chatSession::deliver(chatMsg& msg)
{
    bool writeDone = m_wirteMsg.empty();
    m_wirteMsg.push_back(msg);

    if(writeDone)
    {
        boost::asio::async_write(m_sock, buffer(m_wirteMsg.front().getData(), m_wirteMsg.front().getLen()),
            boost::bind(&chatSession::handler_write, shared_from_this(), boost::asio::placeholders::error));

        m_wirteMsg.pop_front();
    }
    else
    {
        m_pRoom.leave(shared_from_this());
    }

}