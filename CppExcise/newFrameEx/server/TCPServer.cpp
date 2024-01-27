#include "TCPServer.h"
#include "functional"

#include "../comm/resourceManager.h"

void TCPServer::run()
{
    printf("等待连接...\n");
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

    std::string formatStr = getFormatStr("conn uuid = %1%", conn->onlyid());
    printf("连接成功 --> %s\n", formatStr.c_str());

    conn->run();
    run();
}
