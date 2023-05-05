//
// Created by wenheng on 23-4-9.
//

#ifndef BOOST_ASIO_NEW_CHATROOM_H
#define BOOST_ASIO_NEW_CHATROOM_H

#include "deque"
#include "set"

#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/format.hpp"

#include "../netMsg/netMsg.h"
#include "../netResolver/netResolver.h"
//class chatSession;

#include "../CScriptSystem/CScriptSystem.h"
#include "../common/commonClass.h"

using namespace boost::asio::ip;


class chatRoom;
class chatSession : public std::enable_shared_from_this<chatSession>{
public:
    chatSession(boost::asio::io_service& ioserver, chatRoom& room) : m_sessionSocket(ioserver), m_Room(room) {}

    void start();

    void deliver(netMsg& msg);

    bool isVaildConnect();

    tcp::socket& socket() { return m_sessionSocket;}
private:
    tcp::socket m_sessionSocket;
    netMsg m_msg;
    chatRoom& m_Room;


    void handle_readhead(error_code_type ec, size_t bytes);
    void handle_readbody(error_code_type ec, size_t bytes);
    void handle_write(error_code_type ec, size_t bytes);
};

typedef std::set<std::shared_ptr<chatSession>>  SessionQueue;
typedef std::deque<std::shared_ptr<netMsg>> netMsgQueue;
typedef std::shared_ptr<chatSession> chatSessionPtr;

class chatRoom{
public:
    chatRoom() = default;
    chatRoom(const std::vector<netMsg>& netMsgs);
    void deliver(netMsg& msg);
    void join(chatSessionPtr session);
    void leave(chatSessionPtr session);

    void writeToFile();
private:
    SessionQueue m_Sessionqueue;
    netMsgQueue m_Msgqueue;
};

#endif //BOOST_ASIO_NEW_CHATROOM_H
