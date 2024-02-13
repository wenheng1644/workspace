#include "TCPServer_logic.h"
#include "functional"

#include "resourceManager.h"
#include "../logic/userEng.h"

// template <typename T>
void TCPServer_logic::run()
{
    std::string formatStr = getFormatStr("等待连接, threadId = %1%", std::this_thread::get_id());
    printf("TCPServer_logic::run | %s\n", formatStr.c_str());
    conn_tp conn(new TCPConnection_logic(ResourceManager::getObj()->net_io()));

    m_acceptor.async_accept(conn->socket(), std::bind(&TCPServer_logic::onHandleAccept, this, conn, boost::asio::placeholders::error));
}

// template <typename T>
void TCPServer_logic::onHandleAccept(conn_tp conn, ec_code_tp ec)
{
    if(ec || !conn)
    {
        printf("onHandleAccept | error...\n");
        return;
    }

    std::string formatStr = getFormatStr("conn uuid = %1%, threadId = %2%", conn->onlyid(), std::this_thread::get_id());
    printf("TCPServer_logic::onHandleAccept | 连接成功 --> %s\n", formatStr.c_str());

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
