#include "chatSession.h"
#include "boost/bind/bind.hpp"
#include "boost/format.hpp"

#include <iostream>
#include <string>

#include "dateTimeMgr.h"

using namespace boost::asio;
void chatSession::start()
{
    auto readHeadMsg_lam = [this]()
    {
        m_pRoom.join(shared_from_this());
        chatMsg readHeadMsg;

        boost::system::error_code headMsg_ec;
        boost::asio::read(m_sock, buffer(readHeadMsg.getData(), HEADER_LEN), headMsg_ec);

        if(headMsg_ec || !readHeadMsg.decode())
        {
            std::cerr << m_sock.remote_endpoint().address().to_string() << ": " << "头消息读取失败..." << std::endl;
            return;
        }

        boost::system::error_code headMsgUserName_ec;
        boost::asio::read(m_sock, buffer(readHeadMsg.body(), readHeadMsg.bodyLen()), headMsgUserName_ec);

        if(headMsgUserName_ec)
        {
            std::cerr << m_sock.remote_endpoint().address().to_string() << "读取头消息体失败..." << std::endl;
            m_pRoom.leave(shared_from_this());
            return;
        }

        if(strlen(readHeadMsg.body()) == 0)
        {
            std::cerr << "非法数据: " << m_sock.remote_endpoint().address().to_string() << std::endl;
            m_pRoom.leave(shared_from_this());
            return;
        }


        char connectedMsg [100] = {};

        sprintf(connectedMsg, "[connected  (time: %s)\t(ip: %s)\t(name: %s)]",
                dateTimeMgr::getDateTime().c_str(), m_sock.remote_endpoint().address().to_string().c_str(), readHeadMsg.body());

        m_name = std::string (readHeadMsg.body());
        m_ip = m_sock.remote_endpoint().address().to_string();
        std::cout << connectedMsg << std::endl;

        m_pRoom.showChatPartianct();

    };

    std::thread t1(readHeadMsg_lam);
    t1.join();

//    std::cout << "[connect] remote ip: " << m_sock.remote_endpoint().address().to_string() << std::endl;
    memset(m_readingChatMsg.getData(), 0, HEADER_LEN + BODY_LEN);
    m_ip = m_sock.remote_endpoint().address().to_string();
    boost::asio::async_read(m_sock, buffer(m_readingChatMsg.getData(), HEADER_LEN), boost::bind(&chatSession::handler_readhead, shared_from_this(), boost::asio::placeholders::error));
}

void chatSession::handler_readhead(const error_code_type &ec)
{
    if(ec)
    {
        std::cerr << "数据读取错误" << std::endl;
        if(m_sock.available() == 0)
        {
            char tips[100] = {};
            std::sprintf(tips, "[time: %s\tip: %s\tname: %s 客户端已断联]", dateTimeMgr::getDateTime().c_str(), m_ip.c_str(), m_name.c_str());
            std::cerr << tips << std::endl;
        }
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

    //处理用户名
    std::string username_str(m_readingChatMsg.body(), USERNAME_LEN);
    size_t idx = username_str.find_first_of(" ");
    username_str = username_str.substr(0, idx);
    if(username_str.empty() || strlen(username_str.c_str()) == 0) return;

//    m_name = username_str;
    if(username_str != m_name)
    {
        std::cerr << "名字校对错误: " << username_str << "\t" << m_name << std::endl;
    }

    //处理时间日期
    std::string curDateTime = dateTimeMgr::getDateTime();
    printf("[%s (%s   %s)]:\t%s\n", m_sock.remote_endpoint().address().to_string().data(), curDateTime.c_str(), username_str.c_str(), m_readingChatMsg.body() + USERNAME_LEN);
    char msg[BODY_LEN + 1] = "";
    memset(msg, 0, BODY_LEN + 1);


    sprintf(msg,"[%s (%s   %s)]:\t%s\n", m_sock.remote_endpoint().address().to_string().data(), curDateTime.c_str(), username_str.c_str(), m_readingChatMsg.body() + USERNAME_LEN);
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
       std::cerr << "send data error..." << std::endl;
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
