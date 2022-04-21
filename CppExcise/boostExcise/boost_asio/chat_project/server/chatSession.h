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


class chatSession : public chatParticipant, public boost::enable_shared_from_this<chatSession>
{
private:
    chatMsg m_readingChatMsg; //正在读的消息缓存
    ip::tcp::socket m_sock;
    chatRoom& m_pRoom;
    std::deque<chatMsg> m_wirteMsg; //正在写的消息队列

    //连接成功即记录数据，以防报错

public:
    chatSession(io_service& ioserver, chatRoom& room) : m_sock(ioserver), m_pRoom(room) {}
    ~chatSession() {}

    void deliver(chatMsg& msg);

    void start();


    ip::tcp::socket& sock(){
        return m_sock;
    }

    void handler_readhead(const error_code_type& ec);
    void handler_readbody(const error_code_type& ec);
    void handler_write(const error_code_type& ec);

};


#endif