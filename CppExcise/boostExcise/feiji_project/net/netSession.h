//
// Created by wenheng on 23-6-24.
//

#ifndef FEIJI_PROJECT_NETSESSION_H
#define FEIJI_PROJECT_NETSESSION_H

#include "iostream"
#include "memory"

#include "boost/asio.hpp"

#include "../logic/userObj.h"
#include "cmd.h"

#include "deque"
#include "map"

using namespace boost::asio;

class netSession {
public:
    size_t m_onlyid;            //拿时间戳作为唯一id

    netSession(io_service& io) : m_socket(io), m_onlyid(time(nullptr)) {}

    inline ip::tcp::socket& socket() { return m_socket;}

    void close() { m_socket.close();}

    bool operator<(const netSession& v) const;
    bool operator==(const netSession&v) const;

    void operate(bCmd* cmd);
private:
    ip::tcp::socket m_socket;
    userObj m_user;
};

typedef std::shared_ptr<netSession> netSessionPtr;
typedef std::deque<netSessionPtr> netSessionDeque;


#endif //FEIJI_PROJECT_NETSESSION_H
