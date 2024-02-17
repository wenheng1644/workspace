#include "GateUser.h"

gateUser::gateUser(const userComm &comm) : m_comm(comm)
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
        if(msg->head.getProtoValue() == CONNECTION_REQ)
            on_handleConnect(msg);
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

void gateUser::on_handleConnect(netMsg_ptr msg)
{
    auto logicConn = m_logicConn.lock();
    if(!logicConn)
    {
        printf("gateUser::on_handleConnect | 逻辑服句柄已失效\n");
        return;
    }

    auto gateConn = m_conn.lock();
    if(!gateConn)
    {
        printf("gateUser::on_handleConnect | 网关句柄已失效\n");
        return;
    }

    auto ed = gateConn->getaddr();
    logicConn->connect(ed.to_v4().to_string(), 9999);
    
}
