
#ifndef TCPCONNECTION_LOGIC
#define TCPCONNECTION_LOGIC

#include "commServer.h"

#include "boost/enable_shared_from_this.hpp"

#include "vector"
#include "TCPConnection.h"


class user;

class TCPConnection_logic : public TCPConnection , public std::enable_shared_from_this<TCPConnection_logic>
{

public:
    TCPConnection_logic(boost::asio::io_service& io) : TCPConnection(io) {}
    ~TCPConnection_logic() = default;

    void send(const std::vector<char>& buff);
    void send(netMsg_ptr& msg) override;
    void run() override;

    // socket_tp& socket() {return m_sockect;}
    // boost::uuids::uuid onlyid() {return m_onlyid;}

    std::weak_ptr<user> m_target;

private:
    // socket_tp m_sockect;
    // boost::asio::io_service& m_io;
    // boost::uuids::uuid m_onlyid;


    void send(const char* buff, size_t len);

    void on_handleSend(ec_code_tp ec, size_t bytes) override;
    void on_handleReadHead(netMsg_ptr msg, ec_code_tp ec, size_t bytes) override;
    void on_handleReadBody(netMsg_ptr msg, ec_code_tp ec, size_t bytes) override;

};

typedef std::shared_ptr<TCPConnection_logic> TCPConnectionLogic_ptr;

#endif