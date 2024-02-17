#ifndef TCP_GSERVER
#define TCP_GSERVER

#include "TCPServer.h"
#include "commServer.h"
#include "TCP_GConnection.h"

class TCP_GConnection;
class TCP_GServer : public TCPServer<TCP_GConnection>
{
public:
    TCP_GServer(ioserver_tp& io, address_tp add, u_short port);

    void run() override;

private:
    void onHandleAccept(conn_tp conn, ec_code_tp ec) override;
};


#endif