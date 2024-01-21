
#ifndef TCPSEVER
#define TCPSEVER

#include "commServer.h"


class TCPServer
{

public:
    TCPServer(ioserver_tp& io, address_tp& add, u_short port) : m_io(io), m_acceptor(io, endpoint_tp(add, port)) {}
    ~TCPServer() = default;

    void run();
private:
    ioserver_tp& m_io;
    acceptor_tp m_acceptor;

};



#endif
