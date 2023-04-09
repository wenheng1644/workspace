//
// Created by wenheng on 23-3-25.
//

#include "network.h"

void Session::start()
{
    auto lam = [this]()
    {
        m_Room.join(shared_from_this());
        char buff[1024] = {0};
        boost::system::error_code ec;
        this->m_sessionSocket.read_some(boost::asio::buffer(buff, sizeof(netHead)), ec);
        
        if(ec)
        {
            std::cerr << "connect read data error" << std::endl;
            return;
        }
        auto sharedPtr = netResolver::generator()->resolver(buff, sizeof(buff));
        if(!netMsg::isVaildChecknum(sharedPtr->head))
        {
            std::cerr << "resolver head error" << std::endl;
            return;
        }

        this->m_sessionSocket.read_some(boost::asio::buffer(buff + sizeof(netHead), sharedPtr->head.len), ec);
        if(!ec)
        {
            std::cerr << "connect read body error" << std::endl;
            return;
        }

        std::cout << boost::format("connect msg = %s") % (buff + sizeof(netHead)) << std::endl;  
    };

//    lam();
    m_Room.join(shared_from_this());
    m_sessionSocket.async_read_some(boost::asio::buffer(&m_msg.head, sizeof(netHead)), \
        boost::bind(&Session::handle_readhead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Session::handle_readhead(error_code_type ec, size_t bytes)
{
    if(ec || bytes == 0)
    {
        std::cout << boost::format("head info: body len = %d, bytes = %d") % m_msg.head.len % bytes << std::endl;
        std::cerr << "handle_read error;" << std::endl;
        m_Room.leave(shared_from_this());
        return;
    }

    if(!netMsg::isVaildChecknum(m_msg.head))
    {
        std::cerr << "resolver head error" << std::endl;
        return;
    }


    m_sessionSocket.async_read_some(boost::asio::buffer(m_msg.body, m_msg.head.len), \
        boost::bind(&Session::handle_readbody, shared_from_this(), boost::asio::placeholders::error));
}

void Session::handle_readbody(error_code_type ec)
{
    if(strlen(m_msg.body) != m_msg.head.len)
    {
        std::cerr << boost::format("body data error, bodylen = %d, headlen = %d") % strlen(m_msg.body) % m_msg.head.len << std::endl;
        return;
    }

    std::cout << boost::format("body data = %s") % m_msg.body << std::endl;

    m_Room.deliver(m_msg);  //分发数据
    memset(&m_msg.head, 0, sizeof(netHead));
    memset(m_msg.body, 0, sizeof(m_msg.body));

    boost::asio::async_read(m_sessionSocket, boost::asio::buffer(static_cast<void*>(&m_msg.head) , sizeof(netHead)), \
        boost::bind(&Session::handle_readhead, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}


void Session::deliver(netMsg& msg)
{
//    auto data = netResolver::generator()->compose(msg);
    char buff[1024] = {0};
    netResolver::generator()->compose(msg.head, msg.body, msg.head.len, buff);
    boost::asio::async_write(m_sessionSocket, boost::asio::buffer(buff, msg.head.len + sizeof(netHead)), \
        boost::bind(&Session::handle_write, shared_from_this(), boost::asio::placeholders::error));
}

void Session::handle_write(error_code_type ec)
{
    if(ec)
    {
        std::cerr << "handle_write " << std::endl;
        return;
    }
}

void network::run() {
    using namespace boost::system;
    std::cout << "start to listen" << std::endl;
    std::shared_ptr<Session> session_ptr(new Session(m_ioserver, m_Room));
    m_acceptor.async_accept(session_ptr->socket(), boost::bind(&network::handle_accept, this, session_ptr, boost::asio::placeholders::error));

}

void network::handle_accept(std::shared_ptr<Session> session, error_code_type ec)
{
    if(!ec)
    {
        std::string connectMsg = "thank you connect the server!!!";
        netHead head;
        head.len = strlen(connectMsg.data());
        head.type = 1;
        head.version = 0;
        head.checknum = netMsg::makeChceknum(head);
        char buff[1024] = {0};
        netResolver::generator()->compose(head, connectMsg.data(), head.len, buff);
        auto msg_ptr = netResolver::generator()->resolver(buff, sizeof(netHead) + head.len);
        session->deliver(*msg_ptr);   
        session->start();
    }
    run();
}

void Room::deliver(netMsg &msg) {
    for (auto session: m_Sessionqueue) {
        session->deliver(msg);
    }

    while(m_Msgqueue.size() >= 100)
    {
        m_Msgqueue.pop_back();
    }
    m_Msgqueue.push_back(std::shared_ptr<netMsg>(new netMsg(msg)));
}

void Room::join(std::shared_ptr<Session> session) {
    if(m_Sessionqueue.count(session))
        return;
    m_Sessionqueue.insert(session);
    std::cout << boost::format("m_Msgqueue size = %d") % m_Msgqueue.size() << std::endl;
    int index = 0;
    for (std::shared_ptr<netMsg> msg: m_Msgqueue) {
        std::cout << boost::format("index(%d): msg = %s") % (++index) % msg->body << std::endl;
        session->deliver(*msg);
    }
}

void Room::leave(std::shared_ptr<Session> session) {
    if(m_Sessionqueue.empty())
        return;

    if(!m_Sessionqueue.count(session))
        return;

    m_Sessionqueue.erase(session);
}
