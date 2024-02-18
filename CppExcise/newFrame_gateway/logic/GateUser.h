#ifndef GATEUSER
#define GATEUSER

#include "userComm.h"

#include "memory"
#include "queue"
#include "mutex"

#include "commhead.h"

#include "../cmd/gatecmdhead.h"

#include "../TCP_gateway/TCP_GConnection.h"
#include "../TCP_gateway/TCP_LogicConnection.h"

class TCP_GConnection;
class TCP_LogicConnection;
class gateUser
{
public:
    gateUser() = default;
    gateUser(const userComm& comm);

    void processGate();
    void processLogic();

    void push_netMsg(netMsg_ptr msg);
    void push_netLogicMsg(netMsg_ptr msg);

    boost::uuids::uuid onlyid() { return m_onlyid;}

    std::weak_ptr<TCP_GConnection> m_conn;
    std::weak_ptr<TCP_LogicConnection> m_logicConn;

    void close();

private:
    userComm m_comm;
    boost::uuids::uuid m_onlyid;
    std::mutex m_netMsgMutex;
    std::deque<netMsg_ptr> m_netMsgLists;

    std::mutex m_netLogicMutex;
    std::deque<netMsg_ptr> m_netLogicLists;

    std::mutex m_commMutex;


    void on_handleConnect(netMsg_ptr msg);    //处理连接回调
};

typedef std::shared_ptr<gateUser> gateUser_ptr;
#endif