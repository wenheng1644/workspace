//
// Created by нд╨Ц on 2022/5/14.
//

#ifndef SERVER_CHATMSG_H
#define SERVER_CHATMSG_H

#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/bind/bind.hpp"

#include "msgHeader.h"

using namespace boost::asio;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
typedef boost::system::error_code error_code_type;
class chatMsg{
public:
    chatMsg(io_service& ioserver) : m_socket(ioserver) {}
    ~chatMsg() = default;

    ip::tcp::socket& socket()
    {
        return m_socket;
    }

    msgHeader& header()
    {
        return m_header;
    }

private:
    ip::tcp::socket m_socket;
    msgHeader m_header;
};


#endif //SERVER_CHATMSG_H
