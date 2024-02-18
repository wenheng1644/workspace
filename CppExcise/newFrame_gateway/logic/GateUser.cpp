#include "GateUser.h"
#include "../comm/GateManager.h"


gateUser::gateUser(const userComm &comm) : m_comm(comm), m_onlyid(boost::uuids::random_generator()())
{
}

void gateUser::processGate()
{
    std::deque<netMsg_ptr> netMsgLists;
    {
        lockGuard_tp gl(m_netMsgMutex);
        std::swap(m_netMsgLists, netMsgLists);
    }
    

    for(auto msg : netMsgLists)
    {
        // if(msg->head.getProtoValue() == CONNECTION_REQ)
        //     on_handleConnect(msg);
        auto conn = m_logicConn.lock();
        if(conn)
            conn->send(msg);
    }



}

void gateUser::processLogic()
{
    std::deque<netMsg_ptr> netLogicLists;
    {
        lockGuard_tp gl(m_netLogicMutex);
        std::swap(netLogicLists, m_netLogicLists);
    }
    

    for(auto msg : netLogicLists)
    {
        if(msg->head.getProtoValue() == CONNECTION_REQ)
            on_handleConnect(msg);
    }
}

void gateUser::push_netMsg(netMsg_ptr msg)
{
    lockGuard_tp gl(m_netMsgMutex);
    m_netMsgLists.push_back(msg);
}

void gateUser::push_netLogicMsg(netMsg_ptr msg)
{
    lockGuard_tp gl(m_netLogicMutex);
    m_netLogicLists.push_back(msg);
}

void gateUser::close()
{
    auto conn = m_conn.lock();
    if(conn)
    {
        conn->close();
        conn = nullptr;
    }

    auto logic_conn = m_logicConn.lock();
    if(logic_conn)
    {
        logic_conn->close();
        logic_conn = nullptr;
    }
    GateManager::getObj()->m_userEng.erase(m_onlyid);
}

void gateUser::on_handleConnect(netMsg_ptr msg)
{
    // auto logicConn = m_logicConn.lock();
    // if(!logicConn)
    // {
    //     printf("gateUser::on_handleConnect | 逻辑服句柄已失效\n");
    //     return;
    // }

    auto gateConn = m_conn.lock();
    if(!gateConn)
    {
        printf("gateUser::on_handleConnect | 网关句柄已失效\n");
        return;
    }

    // auto ed = gateConn->getaddr();
    // m_logicConn->connect(ed, 9999);
    
}
