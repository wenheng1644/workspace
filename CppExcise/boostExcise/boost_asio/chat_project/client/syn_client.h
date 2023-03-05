//
// Created by нд╨Ц on 2022/4/17.
//

#ifndef CLIENT_SYN_CLIENT_H
#define CLIENT_SYN_CLIENT_H

#include "boost/asio.hpp"

#include "../server/chatMsg.h"

using namespace boost::asio;
class syn_client {
public:
    syn_client(io_service& ioserver, ip::tcp::endpoint& ed) : m_ioserver(ioserver), m_ed(ed){}

    bool connect();

    void write(chatMsg& msg);


private:
    io_service& m_ioserver;
    ip::tcp::endpoint m_ed;
    ip::tcp::socket& m_socket;


    void read_head();
};


#endif //CLIENT_SYN_CLIENT_H
