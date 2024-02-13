#include "user.h"

#include "resourceManager.h"

user::user(const userComm& comm, TCPConnectionLogic_ptr conn) : m_name(comm.name), m_account(comm.account)\
    ,m_age(comm.age), m_sex(comm.sex), m_wTcpConn(conn), m_onlyid(conn->onlyid())
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
        // printf("交换前用户队列包数量 = %d, 临时队列包数量 = %d\n", m_msgLists.size(), curMsgLists.size());
        std::swap(curMsgLists, m_msgLists);
        // printf("交换后用户队列包数量 = %d, 临时队列包数量 = %d\n", m_msgLists.size(), curMsgLists.size());
    }
    // printf("user::run | 用户事件循环 名字 = %s\n", m_name.c_str());
    for(auto& netMsg : curMsgLists)
    {
        //TO-DO
        time_t now = time(nullptr);
        std::string formatStr = getFormatStr("当前包(type = %1%, subtype = %2%) 延迟%3%秒", (int)netMsg->head.type, (int)netMsg->head.subtype, now - netMsg->head.sendtime);
        printf("user::run | %s\n", formatStr.c_str());
        ResourceManager::getObj()->onCallMessage(*netMsg, shared_from_this());

        
        
    }
}

void user::onChatContentMessage(const cmd::chatMessageCmd *msg)
{
    std::string formatStr = getFormatStr("name = %1%, account = %2%, sex = %3%, age = %4%, content = %5%, theadId = %6%",\
         m_name, m_account, (int)m_sex, (int)m_age, msg->content(), std::this_thread::get_id());
    printf("user::onChatContentMessage | %s\n", formatStr.c_str());
}
