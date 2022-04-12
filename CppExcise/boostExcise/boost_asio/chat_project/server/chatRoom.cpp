#include "chatRoom.h"
#include "boost/bind/bind.hpp"

#include "iostream"

void chatRoom::join(participant_ptr particiant)
{
    if(m_sessions.count(particiant))
        return;

    m_sessions.insert(particiant);
    std::cout << "pepole coming...\t" << m_sessions.size() << std::endl;

    std::for_each(m_chatMsgs.begin(), m_chatMsgs.end(), boost::bind(&chatParticipant::deliver, particiant, boost::placeholders::_1));
}

void chatRoom::leave(participant_ptr particiant)
{
    if(m_sessions.empty())
        return;

    if(!m_sessions.count(particiant))
        return;

    std::cout << "pepole leaving...\t" << m_sessions.size() << std::endl;
    m_sessions.erase(particiant);
}


void chatRoom::deliver(chatMsg& msg)
{
    std::cout << "pepoles: " << m_sessions.size() << std::endl;
    if(m_sessions.empty())
        return;
    m_chatMsgs.push_back(msg);
    std::for_each(m_sessions.begin(), m_sessions.end(), std::bind(&chatParticipant::deliver, std::placeholders::_1, msg));
}