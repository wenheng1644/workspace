
#ifndef COMMSERVER
#define COMMSERVER

#include "boost/asio.hpp"
#include "../comm/commhead.h"
#include "../netcomm/net/resolveManager.h"

typedef boost::asio::io_service         ioserver_tp;
typedef boost::asio::ip::address        address_tp;
typedef boost::asio::ip::tcp::socket    socket_tp;
typedef boost::asio::ip::tcp::acceptor  acceptor_tp;
typedef boost::asio::ip::tcp::endpoint  endpoint_tp;

typedef boost::system::error_code       ec_code_tp;






#endif