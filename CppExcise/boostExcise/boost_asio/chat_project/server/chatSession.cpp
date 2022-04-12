#include "chatSession.h"
#include "boost/bind/bind.hpp"

#include <iostream>

void chatSession::start()
{
    m_pRoom.join(shared_from_this());
    memset(m_readingChatMsg.getData(), 0, HEADER_LEN + BODY_LEN);
    std::cout << "[connect] remote ip: " << m_sock.remote_endpoint().address().to_string() << std::endl;
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
        m_pRoom.leave(shared_from_this());
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

//    std::cout << "" <<"reback client msg: " << m_readingChatMsg.body() << std::endl;
    printf("[%s]:\t%s\n", m_sock.remote_endpoint().address().to_string().data(), m_readingChatMsg.body());
    char msg[BODY_LEN + 1] = "";
    memset(msg, 0, BODY_LEN + 1);

    sprintf(msg,"[%s]:\t%s\n", m_sock.remote_endpoint().address().to_string().data(), m_readingChatMsg.body());
    //*******************************************************
    chatMsg newChatMsg;
    memset(newChatMsg.body(), 0, HEADER_LEN + BODY_LEN);
    memcpy(newChatMsg.body(), msg, strlen(msg));
    newChatMsg.bodyLen(strlen(msg));
    newChatMsg.encode();
//    *******************************************************

    m_pRoom.deliver(newChatMsg); //将消息分发给所有客户端
    memset(m_readingChatMsg.getData(), 0, HEADER_LEN + BODY_LEN);

    boost::asio::async_read(m_sock, buffer(m_readingChatMsg.getData(), HEADER_LEN),
                            boost::bind(&chatSession::handler_readhead, shared_from_this(), placeholders::error));
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

}

void chatSession::handler_write(const error_code_type &ec)
{
    if(ec)
    {
//        std::cerr << "send data error..." << std::endl;
        return;
    }
    m_wirteMsg.pop_front();
    if(m_wirteMsg.empty())
    {
//        std::cerr << "datas empty..." << std::endl;
        return;
    }

    boost::asio::async_write(m_sock, buffer(m_wirteMsg.front().getData(), m_wirteMsg.front().getLen()),
                             boost::bind(&chatSession::handler_write, shared_from_this(), placeholders::error));
}
