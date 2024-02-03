
#include "userEng.h"
#include "thread"

UserEng::UserEng() : m_lastRefreshTime(time(nullptr))
{

}

void UserEng::push(user_ptr user)
{
    lockGuard_tp lg(m_userMutex);

    m_userList[user->onlyid()] = user;
}

void UserEng::erase(boost::uuids::uuid onlyid)
{
    lockGuard_tp lg(m_userMutex);
    auto iter = m_userList.find(onlyid);

    if(iter == m_userList.end())
        return;

    m_userList.erase(iter);
}

void UserEng::run()
{
    while(true)
    {
        // printf("UserEng::run| 用户引擎事件循环\n");
        processUser();
        std::this_thread::sleep_for(std::chrono::milliseconds(300));    //睡眠300毫秒
    }
}

void UserEng::processUser()
{
    lockGuard_tp lg(m_userMutex);

    for(auto user_iter : m_userList)
    {
        user_ptr user = user_iter.second;
        if(user)
            user->run();
    }
}
