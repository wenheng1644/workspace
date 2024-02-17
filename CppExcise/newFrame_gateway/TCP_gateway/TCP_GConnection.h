#ifndef TCP_GCONNECTION
#define TCP_GCONNECTION

#include "TCPConnection.h"
#include "commServer.h"

#include "boost/asio.hpp"


#include "../logic/GateUser.h"

class gateUser;
//网关conn
class TCP_GConnection : public TCPConnection, public std::enable_shared_from_this<TCP_GConnection>
{
public:
    TCP_GConnection(ioserver_tp& io);

    void run() override;
    void send(netMsg_ptr& msg) override;

    std::weak_ptr<gateUser> m_target;
    address_tp getaddr();
private:

    void on_handleSend(ec_code_tp ec, size_t bytes) override;
    void on_handleReadHead(netMsg_ptr msg, ec_code_tp ec, size_t bytes) override;
    void on_handleReadBody(netMsg_ptr msg, ec_code_tp ec, size_t bytes) override;

};

#endif