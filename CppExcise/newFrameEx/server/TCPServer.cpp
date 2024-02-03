#include "TCPServer.h"
#include "functional"

#include "../comm/resourceManager.h"
#include "../logic/userEng.h"

void TCPServer::run()
{
    std::string formatStr = getFormatStr("等待连接, threadId = %1%", std::this_thread::get_id());
    printf("TCPServer::run | %s\n", formatStr.c_str());
    TCPConnection_ptr conn(new TCPConnection(ResourceManager::getObj()->net_io()));
    m_acceptor.async_accept(conn->socket(), std::bind(&TCPServer::onHandleAccept, this, conn, boost::asio::placeholders::error));
}

void TCPServer::onHandleAccept(TCPConnection_ptr conn, ec_code_tp ec)
{
    if(ec || !conn)
    {
        printf("onHandleAccept | error...\n");
        return;
    }

    std::string formatStr = getFormatStr("conn uuid = %1%, threadId = %2%", conn->onlyid(), std::this_thread::get_id());
    printf("TCPServer::onHandleAccept | 连接成功 --> %s\n", formatStr.c_str());

    userComm comm;
    comm.account = "aab";
    comm.age = 25;
    comm.name = "邝慧娴";
    comm.sex = female;
    user_ptr connectUser(new user(comm, conn));

    conn->m_target = connectUser;
    UserEng::getObj()->push(connectUser);

    conn->run();
    run();
}
