//
// Created by wenheng on 23-3-26.
//

#ifndef BOOST_ASIO_CLIENT_CLIENT_H
#define BOOST_ASIO_CLIENT_CLIENT_H

#include "boost/asio.hpp"
#include "boost/format.hpp"
#include "boost/bind.hpp"
#include "memory"

#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"

#include "../boost_asio_new/netResolver/netResolver.h"
#include "../boost_asio_new/cmd/base_cmd.h"

#include "../feiji_project/net/playerInfo_cmd.h"
#include "../feiji_project/net/chat_cmd.h"
#include "../boost_asio_new/cmd/playerSys_cmd.h"
#include "../boost_asio_new/cmd/playerChat_cmd.h"

using namespace boost::asio;
class client : public std::enable_shared_from_this<client>{
public:
    client(io_service& ioService, ip::tcp::endpoint ed, const std::string& name)
        : m_socket(ioService), m_ed(ed), m_name(name) {}

    void connect();

private:
    ip::tcp::socket m_socket;
    ip::tcp::endpoint m_ed;
//    netMsg m_msg;
    std::string m_name;

    void handle_connect(boost::system::error_code ec);
    void handle_write();
    
    void handle_readhead(netMsgPtr ptr, boost::system::error_code ec, size_t bytes);
    void handle_readbody(netMsgPtr ptr, boost::system::error_code ec, size_t bytes);

    bool handle_checkConnect();
};


#endif //BOOST_ASIO_CLIENT_CLIENT_H
