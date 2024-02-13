
#ifndef TCPSEVER_LOGIC
#define TCPSEVER_LOGIC

#include "commServer.h"
#include "TCPConnection_logic.h"

#include "commhead.h"

#include "map"

#include "../logic/user.h"
#include "../../commlib/TCP_comm/TCPServer.h"

// template <typename T = TCPConnection_logic>
class TCPServer_logic : public TCPServer<TCPConnection_logic>
{
public:
    TCPServer_logic(ioserver_tp& io, address_tp& add, u_short port) : TCPServer<TCPConnection_logic>(io, add, port) {}
    ~TCPServer_logic() = default;

    void run() override;

    void onHandleAccept(conn_tp conn, ec_code_tp ec) override;

};



#endif
