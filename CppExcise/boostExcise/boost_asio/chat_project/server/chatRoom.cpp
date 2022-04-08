#include "chatRoom.h"
#include "boost\bind\bind.hpp"

bool chatRoom::join(participant_ptr particiant)
{
    if(m_sessions.count(particiant))
        return false;

    m_sessions.insert(particiant);

    return true;
}

bool chatRoom::leave(participant_ptr particiant)
{
    if(m_sessions.empty())
        return false;

    if(!m_sessions.count(particiant))
        return false;

    m_sessions.erase(particiant);

    return true;
}


void chatRoom::deliver(chatMsg& msg)
{
    if(m_sessions.empty())
        return;
    
    std::for_each(m_sessions.begin(), m_sessions.end(), std::bind(&chatSession::deliver, std::placeholders::_1, msg));
}