#ifndef USERENG
#define USERENG

#include "../comm/commhead.h"
#include "../comm/singleton.h"
#include "user.h"

#include "map"

#include "boost/thread.hpp"

//用户引擎
class UserEng : public Singleton<UserEng>
{
public:
    UserEng();
    ~UserEng() = default;

    void push(user_ptr user);
    void erase(boost::uuids::uuid onlyid);

    void run();     //事件循环

private:
    std::mutex m_userMutex;
    std::map<boost::uuids::uuid, user_ptr> m_userList;
    ioserver_tp m_io;
    
    time_t m_lastRefreshTime;

    

    void processUser();     //用户事件循环

};

#endif