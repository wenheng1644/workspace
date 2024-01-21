
#ifndef TCPCONNECTION
#define TCPCONNECTION

#include "commServer.h"

#include "boost/enable_shared_from_this.hpp"

#include "vector"

class TCPConnection : public boost::enable_shared_from_this<TCPConnection>
{

public:
    TCPConnection() = default;
    ~TCPConnection() = default;

    void send(std::vector<char>& buff);
    void run();
private:
    socket_tp m_sockect;


    void on_handleSend(ec_code_tp ec, size_t bytes);
    void on_handleReadHead(ec_code_tp ec, size_t bytes);
    void on_handleReadBody(ec_code_tp ec, size_t bytes);

};

    typedef std::shared_ptr<TCPConnection> TCPConnection_ptr;

#endif