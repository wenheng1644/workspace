
#ifndef CHATROOM_H
#define CHATROOM_H

#define MAX_MSG 512     //存储消息数量上限

#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"
#include <queue>
#include <set>

#include "chatMsg.h"


using namespace boost::asio;

class chatParticipant
{
public:
    virtual ~chatParticipant() {}

    virtual void deliver(chatMsg& msg) = 0;

    std::string ip()
    {
        return m_ip;
    }

    std::string name()
    {
        return m_name;
    }
protected:
    std::string m_ip;
    std::string m_name;
};

typedef boost::shared_ptr<chatParticipant> participant_ptr;

using chatSession_queue = std::set<participant_ptr>; //定义用户队列类型别名
class chatRoom
{
private:
    chatMsg_queue m_chatMsgs;
    chatSession_queue m_sessions;
public:
    void join(participant_ptr particiant);
    void leave(participant_ptr particiant);

    void deliver(chatMsg& msg);

    void showChatPartianct();
};




#endif