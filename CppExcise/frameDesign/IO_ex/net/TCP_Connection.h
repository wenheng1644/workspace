//
// Created by wenheng on 23年12月9日.
//

#ifndef IO_EX_TCP_CONNECTION_H
#define IO_EX_TCP_CONNECTION_H

#include "memory"
#include "boost/asio.hpp"

#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_serialize.hpp"
#include "boost/uuid/uuid_hash.hpp"

class TCP_Connection {
    using TCP = boost::asio::ip::tcp;
public:
    TCP_Connection();

    boost::uuids::uuid uid() const {return m_id;}

private:
    TCP::socket m_fd;
    boost::uuids::uuid m_id;
};

typedef std::shared_ptr<TCP_Connection> TCPConnectionPtr;


#endif //IO_EX_TCP_CONNECTION_H
