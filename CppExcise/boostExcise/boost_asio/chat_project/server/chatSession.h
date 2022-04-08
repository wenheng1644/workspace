#ifndef CHATSESSION_H
#define CHATSESSION_H

#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/enable_shared_from_this.hpp"

#include <queue>

#include "chatMsg.h"
#include "chatRoom.h"

class chatRoom;
using namespace boost::asio;

class chatParticipant
{
public:
    virtual ~chatParticipant() {}

    virtual void deliver(chatMsg& msg) = 0;
};

class chatSession : public chatParticipant, public boost::enable_shared_from_this<chatSession>
{
private:
    chatMsg m_chatMsg;
    ip::tcp::socket& m_sock;
    chatRoom& m_pRoom;
    std::deque<chatMsg> m_wirteMsg;
public:
    chatSession(boost::asio::io_service& ioserver, chatRoom& room) : m_sock(ioserver), m_pRoom(room) {}
    ~chatSession();

    void deliver(chatMsg& msg);

    ip::tcp::socket& sock(){
        return m_sock;
    }

    void start();
    void handler_read(boost::system::error_code ec);
    void handler_write(boost::system::error_code ec);
    
};


#endif