//
// Created by wenheng on 23-6-20.
//

#ifndef FEIJI_PROJECT_NETSERVER_H
#define FEIJI_PROJECT_NETSERVER_H

#include "boost/asio.hpp"
#include "boost/functional.hpp"
#include "mutex"

#include "thread"

#include "cmd.h"
#include "playerInfo_cmd.h"
#include "chat_cmd.h"
#include "netSession.h"


using namespace boost::asio::ip;
class netserver {
public:
    netserver(boost::asio::io_service& ioserver, tcp::endpoint ed);

    void run();

private:
    boost::asio::io_service& m_ioserver;
    tcp::acceptor m_accpter;
    netSessionDeque m_sessions;
    userCmdMap m_userCmds;
    std::mutex m_cmdMutex;

    void handle_accpet(netSessionPtr session, error_code_type ec);
    void handle_readhead(netSessionPtr session, bCmd* cmd,error_code_type ec, size_t bytes);
    void handle_readbody(netSessionPtr session, error_code_type ec, size_t bytes);

    void loop();

    bool isEsixtSessionByOnlyid(size_t onlyid);
    netSessionPtr getNetSessionByOnlyid(size_t onlyid);
};


#endif //FEIJI_PROJECT_NETSERVER_H
