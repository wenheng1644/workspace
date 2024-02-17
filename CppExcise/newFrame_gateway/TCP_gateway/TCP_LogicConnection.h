#ifndef TCP_LOGICCONNECTION
#define TCP_LOGICCONNECTION

#include "TCPConnection.h"
#include "commServer.h"
// #include "commhead.h"

#include "boost/asio.hpp"
#include "memory"

#include "../logic/GateUser.h"

class gateUser;
class TCP_LogicConnection : public TCPConnection , public std::enable_shared_from_this<TCP_LogicConnection>
{
public:
    TCP_LogicConnection(ioserver_tp& io);


    void send(netMsg_ptr& msg) override;

    void connect(address_tp& add, u_char port);

    std::weak_ptr<gateUser> m_target;

private:
    void run() override;

    void on_handleSend(ec_code_tp ec, size_t bytes) override;
    void on_handleReadHead(netMsg_ptr msg, ec_code_tp ec, size_t bytes) override;
    void on_handleReadBody(netMsg_ptr msg, ec_code_tp ec, size_t bytes) override;

    void on_handleConnection(ec_code_tp ec);
};

#endif