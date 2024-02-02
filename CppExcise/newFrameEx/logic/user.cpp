#include "user.h"

user::user(const userComm& comm, TCPConnection_ptr conn) : m_name(comm.name), m_account(comm.account)\
    ,m_age(comm.age), m_sex(comm.sex), m_wTcpConn(conn)
{

}

void user::push_netMsg(netMsg_ptr msg)
{
    if(!msg) return;
    lockGuard_tp lg(m_msgListMutex);
    m_msgLists.push_back(msg);
}

void user::run()
{
    std::deque<netMsg_ptr> curMsgLists;
    {
        lockGuard_tp lg(m_msgListMutex);
        std::swap(curMsgLists, m_msgLists);
    }

    for(auto& netMsg : curMsgLists)
    {
        //TO-DO
        
    }
}

void user::onChatContentMessage(cmd::chatMessageCmd *msg)
{
    std::string formatStr = getFormatStr("name = %s, account = %s, sex = %d, age = %d", m_name, m_account, (int)m_sex, (int)m_age);
    printf("user::onChatContentMessage | %s\n", formatStr.c_str());
}
