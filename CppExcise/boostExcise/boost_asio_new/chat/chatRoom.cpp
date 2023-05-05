//
// Created by wenheng on 23-4-9.
//

#include "chatRoom.h"

void chatRoom::deliver(netMsg &msg) {
    for(auto session : m_Sessionqueue)
    {
        session->deliver(msg);
    }

    while(m_Msgqueue.size() >= 100)
        m_Msgqueue.pop_back();

    m_Msgqueue.push_back(std::shared_ptr<netMsg>(new netMsg(msg)));
}

void chatRoom::join(chatSessionPtr session)
{
    if(m_Sessionqueue.count(session))
        return;
    m_Sessionqueue.insert(session);

    std::cout << boost::format("m_msgqueue size = %d") % m_Msgqueue.size() << std::endl;
    for(auto msg : m_Msgqueue)
        session->deliver(*msg);
}

void chatRoom::leave(chatSessionPtr session)
{
    if(!m_Sessionqueue.count(session))
        return;

    m_Sessionqueue.erase(session);
}

chatRoom::chatRoom(const std::vector<netMsg> &netMsgs)
{
    for(netMsg msg : netMsgs)
    {
        std::shared_ptr<netMsg> ptr(new netMsg);
        ptr->head.len = msg.head.len;
        ptr->head.type = msg.head.type;
        ptr->head.version = msg.head.version;
        ptr->head.checknum = msg.head.checknum;
        ptr->head.info.times = msg.head.info.times;
        memcpy(ptr->head.info.ip, msg.head.info.ip, sizeof(msg.head.info.ip));
        memcpy(ptr->head.info.name, msg.head.info.name, sizeof(msg.head.info.name));
        memcpy(ptr->body, msg.body, sizeof(msg.body));

        m_Msgqueue.push_back(ptr);
    }
}

void chatRoom::writeToFile()
{
    CScriptSystem *lua = CScriptSystem::getSingalton();
    netMsgList netMsgs;

    for(const auto ptr : m_Msgqueue)
    {
        netMsgs.push_back(*ptr);
    }
    lua->clua_wirtefile(netMsgs);
    std::cout << "chatRoom::writeToFile | write to file done" << std::endl;
}


void chatSession::start()
{
    m_Room.join(shared_from_this());
    m_sessionSocket.async_read_some(boost::asio::buffer(&m_msg.head, sizeof(netHead)), \
        boost::bind(&chatSession::handle_readhead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void chatSession::deliver(netMsg &msg)
{
    using namespace boost::asio;
    char buff[1024] = {0};
    netResolver::generator()->compose(msg.head, msg.body, msg.head.len, buff);
    m_sessionSocket.async_write_some(boost::asio::buffer(buff, sizeof(netHead) + msg.head.len), boost::bind(&chatSession::handle_write, shared_from_this(), \
        placeholders::error, placeholders::bytes_transferred));
}

void chatSession::handle_readhead(error_code_type ec, size_t bytes)
{
    using namespace boost::asio;

    if(ec)
    {
        std::cerr << "handle_readhead | ec" << std::endl;
        return;
    }

    if(bytes == 0)
    {
        std::cerr << "handle_readhead | per socket closed..." << std::endl;
        m_Room.leave(shared_from_this());
        m_sessionSocket.close();
        return;
    }

    if(!netMsg::isVaildChecknum(m_msg.head))
    {
        std::cerr << "handle_readhead | not a vaild msg" << std::endl;
        return;
    }

    m_sessionSocket.async_read_some(boost::asio::buffer(m_msg.body, m_msg.head.len), boost::bind(&chatSession::handle_readbody, shared_from_this(), \
        placeholders::error, placeholders::bytes_transferred));
}

void chatSession::handle_readbody(error_code_type ec, size_t bytes)
{
    if(ec)
    {
        std::cerr << "handle_readbody | ec" << std::endl;
        return;
    }

    std::cout << boost::format("read data(%d): %s") % bytes % m_msg.body << std::endl;
    m_Room.deliver(m_msg);
    std::memset(m_msg.body, 0, 1024);
    m_sessionSocket.async_read_some(boost::asio::buffer(&m_msg.head, sizeof(netHead)), \
        boost::bind(&chatSession::handle_readhead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void chatSession::handle_write(error_code_type ec, size_t bytes)
{
    if(ec)
    {
        std::cout << boost::format("handle_write error, bytes = %d") % bytes << std::endl;
        return;
    }
}

bool chatSession::isVaildConnect()
{
    char buff[1024] = {0};
    boost::system::error_code ec;
    size_t bytes = m_sessionSocket.read_some(boost::asio::buffer(buff, sizeof(netHead)), ec);

    if(ec)
    {
        std::cerr << "isVaildConnect error" << std::endl;
        m_sessionSocket.close();
        return false;
    }

    if(bytes == 0 || bytes != sizeof(netHead))
    {
        std::cerr << boost::format("pre socket has done..., bytes = %d") % bytes << std::endl;
        m_sessionSocket.close();
        return false;
    }

    netHead head = netResolver::generator()->getNetHead(buff);

    return netMsg::isVaildChecknum(head);
}