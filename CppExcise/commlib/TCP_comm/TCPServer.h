
#ifndef TCPSEVER
#define TCPSEVER

#include "commServer.h"
#include "TCPConnection.h"

#include "../comm/commhead.h"

#include "map"
#include "memory"

template <typename T>
class TCPServer
{
public:
    TCPServer(ioserver_tp& io, address_tp& add, u_short port) : m_io(io), m_acceptor(io, endpoint_tp(add, port)) {}
    virtual ~TCPServer() {}

    virtual void run() = 0;

protected:
    ioserver_tp& m_io;
    acceptor_tp m_acceptor;

    typedef std::shared_ptr<T> conn_tp;


    virtual void onHandleAccept(conn_tp conn, ec_code_tp ec);

};


// template <typename T>
// void TCPServer<T>::run()
// {
//     std::string formatStr = getFormatStr("等待连接, threadId = %1%", std::this_thread::get_id());
//     printf("TCPServer::run | %s\n", formatStr.c_str());
//     conn_tp conn(new T(m_io));
//     m_acceptor.async_accept(conn->socket(), std::bind(&TCPServer::onHandleAccept, this, conn, boost::asio::placeholders::error));
// }

template <typename T>
void TCPServer<T>::onHandleAccept(conn_tp conn, ec_code_tp ec)
{
    if(ec || !conn)
    {
        printf("onHandleAccept | error...\n");
        return;
    }

    std::string formatStr = getFormatStr("conn uuid = %1%, threadId = %2%", conn->onlyid(), std::this_thread::get_id());
    printf("TCPServer::onHandleAccept | 连接成功 --> %s\n", formatStr.c_str());

    conn->run();
    run();
}


#endif
