//
// Created by wenheng on 23-4-9.
//

#ifndef BOOST_ASIO_NEW_CHATROOM_H
#define BOOST_ASIO_NEW_CHATROOM_H

#include "deque"
#include "set"
#include "mutex"

#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/format.hpp"

#include "../netMsg/netMsg.h"
#include "../netResolver/netResolver.h"
//class chatSession;

#include "../CScriptSystem/CScriptSystem.h"
#include "../common/commonClass.h"
#include "../common/user.h"
#include "../cmd/base_cmd.h"
#include "../cmd/playerSys_cmd.h"
#include "../cmd/playerChat_cmd.h"

using namespace boost::asio::ip;


class chatRoom;
class chatSession : public std::enable_shared_from_this<chatSession>{
public:

    chatSession(boost::asio::io_service& ioserver, chatRoom& room) :
        m_sessionSocket(ioserver), m_Room(room) {}

//    chatSession() = default;

    void start();

    void deliver(netMsg& msg);

    bool isVaildConnect();

    bool test_vaildConnect();

    inline tcp::socket& socket() { return m_sessionSocket;}

    inline void setname(const std::string& name)
    {
        if(name != m_user.name())
            m_user.setname(name);
    }

    inline std::string name()
    {
        return m_user.name();
    }

    inline user getuserinfo() { return m_user;}

    inline std::string ip()
    {
        return m_sessionSocket.remote_endpoint().address().to_string();
    }

    inline size_t port()
    {
        return m_sessionSocket.remote_endpoint().port();
    }

    bool close();

    void runNetMsg();

private:
    tcp::socket m_sessionSocket;
    netMsg m_msg;
    chatRoom& m_Room;
//    std::string m_name;
    user m_user;

    std::mutex m_NetMsgMutex;
    netMsgQueue m_dataNetMsg;


    void handle_readhead(std::shared_ptr<netMsg> p, error_code_type ec, size_t bytes);
    void handle_readbody(std::shared_ptr<netMsg>p, error_code_type ec, size_t bytes);
    void handle_write(error_code_type ec, size_t bytes);


    void onHandleMsg(const netMsg& msg);

//    void onPlayConnectMsg(const netMsg& msg);
    void sendConnectRetMsg(playerConnectCmd_Ret& cmd, const std::string& conntent);
    void sendNetMsg(const netMsg& msg);


    void onPlayChatMsg(const netMsg& msg);
    void onPlayCheckInfo(const netMsg& msg);
    void onPlaySendUserChat(const netMsg& msg);
    void onPlayOnlineCountUser(const netMsg& msg);
};

typedef std::set<std::shared_ptr<chatSession>>  SessionQueue;
typedef std::shared_ptr<chatSession> chatSessionPtr;

//起到管理所有会话的效果
class chatRoom{
public:
    chatRoom() = default;
    chatRoom(const std::vector<netMsg>& netMsgs);
    void deliver(netMsg& msg, bool isSave = true);
    void deliver(const std::string& name, netMsg& msg);
    void join(chatSessionPtr session);
    bool leave(chatSessionPtr session);

    void writeToFile();
    void printMsgs();

    void runChatSession();

    std::shared_ptr<chatSession> findChatSeesion(const std::string& name);


//private:
    SessionQueue m_Sessionqueue;
    netMsgQueue m_Msgqueue;

//private:
    static std::mutex m_SessionMutex;

private:
    void sendOnlineCountMsg();

};

#endif //BOOST_ASIO_NEW_CHATROOM_H
