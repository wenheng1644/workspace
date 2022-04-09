//
// Created by 文恒 on 2022/4/9.
//

#ifndef SERVER2_SERVER_HPP
#define SERVER2_SERVER_HPP

#define MAX_MSG 512

#include <set>
#include <queue>
#include "chatMsg.hpp"

#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "boost/bind/bind.hpp"
using namespace boost::asio;


class particant
{
public:
    particant(){}
    virtual ~particant() {}
    virtual void deliver(chatMsg& msg) = 0;
};
typedef boost::shared_ptr<particant> particant_ptr;

typedef std::deque<chatMsg> queueMsg;
class chatRoom
{
public:
    chatRoom() {}

    void join(particant_ptr p)
    {
        if(m_particants.count(p) != 0)
            return;

        m_particants.insert(p);

        std::for_each(m_Msgs.begin(), m_Msgs.end(), boost::bind(&particant::deliver, p, boost::placeholders::_1));
    }

    void leave(particant_ptr p)
    {
        if(m_particants.count(p) == 0)
            return;

        m_particants.erase(p);
    }

    void deliver(chatMsg& msg)
    {
        m_Msgs.push_back(msg);
        while(m_Msgs.size() > MAX_MSG)
            m_Msgs.pop_front();
        std::for_each(m_particants.begin(), m_particants.end(),
                      boost::bind(&particant::deliver, boost::placeholders::_1, boost::ref(msg)));
    }

private:
    std::set<particant_ptr> m_particants;
    queueMsg  m_Msgs;

};

class chatSession : public particant, public boost::enable_shared_from_this<chatSession>
{
public:
    chatSession(io_service& ioserver, chatRoom& room) : m_socket(ioserver), m_room(room) {}

    void start()
    {
        m_room.join(shared_from_this());

        read();
    }

    void deliver(chatMsg& msg)
    {
        std::cout << "chatSession rec: " << msg.data() << std::endl;
    }

    void read()
    {
        boost::asio::async_read(m_socket, buffer(m_msg.data(), m_msg.length()),
                                                 boost::bind(&chatSession::hander_read, shared_from_this(), boost::asio::placeholders::error));
    }

    void write()
    {
        while(!m_wirtingMsg.empty())
        {
            boost::asio::async_write(m_socket, buffer(m_wirtingMsg.front().data(), m_wirtingMsg.front().length())
            , boost::bind(&chatSession::hander_write, shared_from_this(), boost::asio::placeholders::error));
        }
    }

    ip::tcp::socket& socket()
    {
        return m_socket;
    }
private:
    ip::tcp::socket m_socket;
    chatRoom& m_room;
    chatMsg m_msg;
    queueMsg m_wirtingMsg;

    void hander_read(boost::system::error_code ec)
    {
        if(!ec)
        {
            std::cout << "rec: " << m_msg.data() << std::endl;
        }
        else
        {
            std::cerr << "rec error" << std::endl;
        }
    }

    void hander_write(boost::system::error_code ec)
    {
        if(!m_wirtingMsg.empty() && !ec)
        {
            m_wirtingMsg.pop_front();
            boost::asio::async_write(m_socket, buffer(m_wirtingMsg.front().data(), m_wirtingMsg.front().length()),
                                     boost::bind(&chatSession::hander_write, shared_from_this(), boost::asio::placeholders::error));
        }
    }

};

typedef boost::shared_ptr<chatSession> chatSession_ptr;
class chatServer
{
public:
    chatServer(io_service& ioserver, ip::tcp::endpoint& ed) : m_ioserver(ioserver), m_acceptor(ioserver, ed) {}

    void run()
    {
        chatSession_ptr session(new chatSession(m_ioserver, m_room));
        m_acceptor.async_accept(session->socket(),
                                boost::bind(&chatServer::hander_run, this, session, boost::asio::placeholders::error));
    }

    void hander_run(chatSession_ptr session, boost::system::error_code ec)
    {
        if(!ec)
            session->start();

        run();
    }

private:
    io_service& m_ioserver;
    chatRoom m_room;
    ip::tcp::acceptor m_acceptor;
};
#endif //SERVER2_SERVER_HPP
