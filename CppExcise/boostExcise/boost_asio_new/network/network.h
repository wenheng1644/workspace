//
// Created by wenheng on 23-3-25.
//

#ifndef BOOST_ASIO_NEW_NETWORK_H
#define BOOST_ASIO_NEW_NETWORK_H

#define BYTESLEN 1024

#include "iostream"
#include "string"
#include "memory"
#include "queue"
#include "set"

#include "boost/format.hpp"
#include "boost/asio.hpp"
#include "functional"
#include "binders.h"
#include "boost/bind/bind.hpp"
#include "boost/chrono.hpp"
#include "boost/chrono/chrono.hpp"

#include "../netResolver/netResolver.h"
#include "../netMsg/netMsg.h"
#include "../chat/chatRoom.h"
#include "../common/commonClass.h"

#include "sol/sol.hpp"

class network {
public:
    network(boost::asio::io_service&  ioserver, tcp::endpoint ed, std::vector<netMsg> netMsgs);

    void run();
    void stop();
    ~network();

    void lua_loadFunc();
private:
    boost::asio::io_service& m_ioserver;
    tcp::acceptor m_acceptor;
    chatRoom m_Room;
    time_with_func m_timer;

    void handle_accept(chatSessionPtr session, error_code_type ec);

    chatRoom& getRoom() { return m_Room; }
    void writeToFile();
};

#endif //BOOST_ASIO_NEW_NETWORK_H
