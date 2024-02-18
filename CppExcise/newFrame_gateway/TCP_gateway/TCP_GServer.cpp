#include "TCP_GServer.h"
#include "../comm/GateManager.h"
#include "../logic/GateUserEng.h"
#include "thread"

#include "boost/asio.hpp"

TCP_GServer::TCP_GServer(ioserver_tp &io, address_tp add, u_short port) : TCPServer<TCP_GConnection>(io, add, port)
{

}

void TCP_GServer::run()
{

    std::string formatstr = getFormatStr("等待连接...  threadid = %1%", std::this_thread::get_id());
    printf("TCP_GServer::run | 网关服 ---> %s\n", formatstr.c_str());
    conn_tp conn(new TCP_GConnection(GateManager::getObj()->clientIO()));
    m_acceptor.async_accept(conn->socket(), std::bind(&TCP_GServer::onHandleAccept, this, conn, boost::asio::placeholders::error));
    
}

void TCP_GServer::onHandleAccept(conn_tp conn, ec_code_tp ec)
{
    if(ec || !conn)
    {
        std::string formatstr = getFormatStr("error content = %1%", ec.message());
        printf("TCP_GServer::onHandleAccept | 网关服链接失败... %s\n", formatstr.c_str());
        conn->close();

        return;
    }

    //TO--DO 网关服处理
    userComm comm;
    comm.m_account = "xwz1644";
    comm.m_name = "xwz";
    comm.m_age = 25;
    comm.m_passwd = "xwz111598";
    comm.m_sex = male;
    gateUser_ptr user(new gateUser(comm));

    user->m_conn = conn;
    conn->m_target = user;

    std::shared_ptr<TCP_LogicConnection> logicConn(new TCP_LogicConnection(GateManager::getObj()->serverIO()));
    user->m_logicConn = logicConn;
    logicConn->m_target = user;
    GateManager::getObj()->m_userEng.push(user);
    conn->run();

    auto ed = m_acceptor.local_endpoint();
    address_tp add = ed.address();
    logicConn->connect(add, 9999);
    run();
}
