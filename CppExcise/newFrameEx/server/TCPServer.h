
#ifndef TCPSEVER
#define TCPSEVER

#include "commServer.h"
#include "TCPConnection.h"

#include "../comm/commhead.h"

#include "map"

class TCPServer
{

public:
    TCPServer(ioserver_tp& io, address_tp& add, u_short port) : m_io(io), m_acceptor(io, endpoint_tp(add, port)) {}
    ~TCPServer() = default;

    void run();
private:
    ioserver_tp& m_io;
    acceptor_tp m_acceptor;

    void onHandleAccept(TCPConnection_ptr conn, ec_code_tp ec);

};



#endif
