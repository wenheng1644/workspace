
#ifndef TCPCONNECTION
#define TCPCONNECTION

#include "commServer.h"

#include "boost/enable_shared_from_this.hpp"

#include "vector"

#include "mutex"

class TCPConnection
{

public:
    TCPConnection(boost::asio::io_service& io) : m_io(io), m_sockect(io), m_onlyid(boost::uuids::random_generator()()) {}
    virtual ~TCPConnection() { close(); }

    // void send(const std::vector<char>& buff);
    virtual void send(netMsg_ptr& msg) = 0;
    virtual void run() = 0;

    socket_tp& socket() {return m_sockect;}
    boost::uuids::uuid onlyid() {return m_onlyid;}

    virtual bool close();

protected:
    std::mutex m_socketMutex;
    socket_tp m_sockect;
    boost::asio::io_service& m_io;
    boost::uuids::uuid m_onlyid;


    // void send(const char* buff, size_t len);

    virtual void on_handleSend(ec_code_tp ec, size_t bytes) = 0;
    virtual void on_handleReadHead(netMsg_ptr msg, ec_code_tp ec, size_t bytes) = 0;
    virtual void on_handleReadBody(netMsg_ptr msg, ec_code_tp ec, size_t bytes) = 0;

};

typedef std::shared_ptr<TCPConnection> TCPConnection_ptr;

#endif