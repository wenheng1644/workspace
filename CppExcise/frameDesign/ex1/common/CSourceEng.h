//
// Created by wenheng on 23年9月26日.
//

#ifndef EX1_CSOURCEENG_H
#define EX1_CSOURCEENG_H

#include "shared_mutex"

#include "boost/thread.hpp"

#include "../TCP_Server/Session.h"
#include "threadSafe_Container.h"
#include "task.h"
#include "../logManager/logManager.h"
#include "../logic/chatRecordManager.h"

#include "../logic/user.h"

#include "timer.h"

#include "task.h"

template<typename T>
class Sington
{
public:
    static T* getMe()
    {
        std::unique_lock uniqueLock(m_mutex_);
        if(!m_obj_)
        {
            m_obj_ = new T;
        }
        return m_obj_;
    }

    virtual ~Sington()
    {
        if(m_obj_)
            delete m_obj_;
    }

protected:
    static T* m_obj_;
    static std::shared_mutex m_mutex_;
    Sington() = default;
};

template<typename  T>
T* Sington<T>::m_obj_ = nullptr;

template<typename  T>
std::shared_mutex Sington<T>::m_mutex_;

typedef threadSafe_Container<TaskPtr> TaskQueue;

class CSourceEng : public Sington<CSourceEng>{
public:
    void stratup();
    ~CSourceEng();

    UserPtr makeNewUser(SessionPtr session);
    bool addNewUser(UserPtr newUser);
    bool removeUser(UserPtr newUser);
    void addToAllUser(TaskPtr task);
    bool isUserExistByAccount(const std::string& account);
    void noticeAllLogin();
    void recordChat(UserPtr user, const std::string& content);
    void chatRecordToDB();

    SessionManager m_SessionManager_;
private:
    boost::thread_group m_IOThreadGroups_;
    LogManager m_logManger;
//    userManager m_userManager_;
    std::shared_ptr<userManager> m_userManager_;
    chatRecordManager m_chatRecord;
//    CSourceEng(){}

    void handle_AccpetIOThread();
    void handle_DisConnectIOThread();
    void handle_SendPackThread();
    void handle_RunUsers();


};



#endif //EX1_CSOURCEENG_H
