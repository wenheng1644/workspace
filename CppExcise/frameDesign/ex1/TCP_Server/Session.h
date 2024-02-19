//
// Created by wenheng on 23年9月23日.
//

#ifndef EX1_SESSION_H
#define EX1_SESSION_H

#include "boost/asio.hpp"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_serialize.hpp"
#include "boost/uuid/uuid_hash.hpp"

#include "boost/bind.hpp"

#include "boost/format.hpp"
#include "iostream"
#include "memory"

#include "../common/threadSafe_Container.h"
#include "../common/task.h"
#include "../common/timer.h"

#include "../netResolver/user_cmd.h"



typedef boost::uuids::uuid UUID;

typedef boost::system::error_code error_code_type;

using namespace boost::asio::ip;

class SessionManager;

class Session : public std::enable_shared_from_this<Session>{
    friend class SessionManager;
public:
    Session() = delete;
//    Session(const Session& other) = delete;
//    Session& operator=(const Session& other) = delete;

    Session(boost::asio::io_service& io);

    bool operator==(const Session& other);
    void run();
    void close();
    void startTimer();

    void send(TaskPtr task);
    void read(TaskPtr task);
    bool isVaild();

    void update_heartBeat();
    bool handle_sendHeartBeat(u_char type, u_char subtype);

    void swapTasks(std::deque<TaskPtr>& queue);

    bool checkLogin();

    UUID m_uuid_;
    tcp::socket m_fd;

    userData m_userData;
private:
    time_with_func m_timer_;
    time_t m_lastUpDateTimeZone;
    threadSafe_Container<Task> m_netTask_;      //业务数据待处理消息队列
    threadSafe_Container<Task> m_SendTask_;     //业务数据待发送消息队列

    void sendDataPacks();

    void send(const std::string& ser_str, size_t len);

    void handle_send(error_code_type ec, size_t bytes);
    void handle_checkHeartBeat();


    void handle_readhead(netMsgPtr data, error_code_type  ec, size_t bytes);
    void handle_readbody(netMsgPtr data, error_code_type  ec, size_t bytes);
};

typedef std::shared_ptr<Session> SessionPtr;


class SessionManager
{
public:
    SessionManager() = default;

    void handle_SendPackData();
    void closeAll();
    threadSafe_Container<Session> m_waitConnectSessions;
    threadSafe_Container<Session> m_waitDisConnectSessions;
    threadSafe_Container<Session> m_onlineSessions;


private:
};


#endif //EX1_SESSION_H
