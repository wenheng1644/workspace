
#ifndef TCPCONNECTION
#define TCPCONNECTION

#include "commServer.h"

#include "boost/enable_shared_from_this.hpp"

#include "vector"

class user;

class TCPConnection : public std::enable_shared_from_this<TCPConnection>
{

public:
    TCPConnection(boost::asio::io_service& io) : m_io(io), m_sockect(io), m_onlyid(boost::uuids::random_generator()()) {}
    ~TCPConnection() = default;

    void send(const std::vector<char>& buff);
    void send(netMsg_ptr& msg);
    void run();

    socket_tp& socket() {return m_sockect;}
    boost::uuids::uuid onlyid() {return m_onlyid;}

    std::weak_ptr<user> m_target;

private:
    socket_tp m_sockect;
    boost::asio::io_service& m_io;
    boost::uuids::uuid m_onlyid;


    void send(const char* buff, size_t len);

    void on_handleSend(ec_code_tp ec, size_t bytes);
    void on_handleReadHead(netMsg_ptr msg, ec_code_tp ec, size_t bytes);
    void on_handleReadBody(netMsg_ptr msg, ec_code_tp ec, size_t bytes);

};

    typedef std::shared_ptr<TCPConnection> TCPConnection_ptr;

#endif