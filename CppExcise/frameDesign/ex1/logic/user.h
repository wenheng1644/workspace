//
// Created by wenheng on 23年10月19日.
//

#ifndef EX1_USER_H
#define EX1_USER_H

#include "iostream"

#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_serialize.hpp"
#include "boost/uuid/uuid_hash.hpp"

#include "../TCP_Server/Session.h"
#include "../common/task.h"


class userManager;

class user : public std::enable_shared_from_this<user>{
public:
    explicit user(SessionPtr session, std::shared_ptr<userManager> userManager);
    bool isVaild();
    void init_userData(const userData& data);

    bool operator==(const user& other);
    bool operator==(SessionPtr session);
    void hanldeTask();
    void addTask(TaskPtr task);

    Sex sex(){ return m_sex_;}
    std::string name() {return m_name;}
    void online(bool status);
    bool online();
    u_char gmlv() {return m_gmlevel;}

    bool isMe(boost::uuids::uuid sessionid);

private:
    Sex m_sex_;                 //性別
    size_t m_dailyOnlineTimes;  //
    time_t m_lastLoginTimeZone; //
    u_char m_gmlevel;
    boost::uuids::uuid m_onylyId;
    bool m_isOnline;
    std::string m_name;
    std::weak_ptr<Session> m_connecthandle;
    std::weak_ptr<userManager> m_userManager;
    std::shared_mutex m_mutex;

    bool isVaildWithNoMutex();


};

typedef std::shared_ptr<user> UserPtr;

class userManager
{
public:
    userManager() = default;

    void run();

    void remove(SessionPtr session);
    void remove(UserPtr user);
    void push(UserPtr user);
    UserPtr findUser(SessionPtr session);
    UserPtr findUser(const std::string& account);

    void addToAllUser(TaskPtr task);
    size_t onlineCnt();
    std::vector<UserPtr> getOnlineUserList();
private:
    threadSafe_Container<user> m_users;
    std::mutex m_mutex;

    UserPtr findUserWithNoMutex(SessionPtr session);
    UserPtr findUserWithNoMutex(const std::string& account);
};
#endif //EX1_USER_H
