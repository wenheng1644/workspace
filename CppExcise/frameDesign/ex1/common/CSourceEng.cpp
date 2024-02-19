//
// Created by wenheng on 23年9月26日.
//

#include "CSourceEng.h"
#include "comm_func.h"

#include "../logic/user.h"

void CSourceEng::stratup()
{
    m_userManager_ = std::shared_ptr<userManager>(new userManager);
    m_chatRecord.setUserManager(m_userManager_);

    m_IOThreadGroups_.create_thread(boost::bind(&CSourceEng::handle_AccpetIOThread, this));
    m_IOThreadGroups_.create_thread(boost::bind(&CSourceEng::handle_DisConnectIOThread, this));
    m_IOThreadGroups_.create_thread(boost::bind(&CSourceEng::handle_SendPackThread, this));
    m_IOThreadGroups_.create_thread(boost::bind(&CSourceEng::handle_RunUsers, this));
}

void CSourceEng::handle_AccpetIOThread()
{
    while(true)
    {
        {
            std::unique_lock<std::shared_mutex> uniqueLock(m_SessionManager_.m_waitConnectSessions.m_mutex_);
            m_SessionManager_.m_waitConnectSessions.m_cond_.wait(uniqueLock);

            uniqueLock.unlock();
            auto session = m_SessionManager_.m_waitConnectSessions.pop();

            BOOST_LOG_TRIVIAL(info) << commfunc::getFormatStr("handle_AccpetIOThread | session = [%1% : %2%]", session->m_uuid_, std::this_thread::get_id());
            session->update_heartBeat();
            session->startTimer();
            session->run();

//            std::unique_lock<std::shared_mutex> gl(m_SessionManager_.m_onlineSessions.m_mutex_);
            m_SessionManager_.m_onlineSessions.push(session);
//            UserPtr  user1(new user(session));
            UserPtr  user1 = makeNewUser(session);
            user1->init_userData(session->m_userData);
            addNewUser(user1);
            m_chatRecord.onUserLogin(user1);
        }



        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

CSourceEng::~CSourceEng()
{
    m_IOThreadGroups_.join_all();
}

void CSourceEng::handle_DisConnectIOThread()
{
    while(true)
    {
        {
            std::unique_lock<std::shared_mutex> uniqueLock(m_SessionManager_.m_waitDisConnectSessions.m_mutex_);
            m_SessionManager_.m_waitDisConnectSessions.m_cond_.wait(uniqueLock);

            uniqueLock.unlock();

            auto session = m_SessionManager_.m_waitDisConnectSessions.pop();
            BOOST_LOG_TRIVIAL(info) << commfunc::getFormatStr("handle_DisConnectIOThread | session[%1%] remove",\
                session->m_uuid_);

//            std::unique_lock<std::shared_mutex> gl(m_SessionManager_.m_onlineSessions.m_mutex_);
            m_SessionManager_.m_onlineSessions.remove(session);
//            m_userManager_.remove(session);
            UserPtr findUser = m_userManager_->findUser(session);
            if(findUser)
            {
                findUser->online(false);
                removeUser(findUser);
            }
            else
            {
                BOOST_LOG_TRIVIAL(error) << commfunc::getFormatStr("handle_DisConnectIOThread | session[%1%] findUser error",\
                    session->m_uuid_);
            }

        }
        std::this_thread::sleep_for(std::chrono::milliseconds(300));

    }
}

void CSourceEng::handle_SendPackThread()
{
    BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("handle_SendPackThread | session 任务Loop");
    while(true)
    {
        m_SessionManager_.handle_SendPackData();

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}

void CSourceEng::handle_RunUsers()
{
    while(true)
    {
        m_userManager_->run();

        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

}

bool CSourceEng::addNewUser(UserPtr newUser)
{
    if(!newUser) return false;

    m_userManager_->push(newUser);
    BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("addUser |add user[%s], sex[%d]",\
                newUser->name() , (int)newUser->sex());
    noticeAllLogin();
    return true;
}

bool CSourceEng::removeUser(UserPtr newUser)
{
    if(!newUser) return false;

    m_userManager_->remove(newUser);
    BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("removeUser |remove user[%s], sex[%d]",\
                newUser->name() , (int)newUser->sex());
    noticeAllLogin();
    return true;
}

void CSourceEng::addToAllUser(TaskPtr task)
{
    m_userManager_->addToAllUser(task);
}

UserPtr CSourceEng::makeNewUser(SessionPtr session)
{
    if(!session) return UserPtr();
    UserPtr connectUser(new user(session, m_userManager_));
    return connectUser;
}

void CSourceEng::noticeAllLogin()
{
    auto onlineList = m_userManager_->getOnlineUserList();

    BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("noticeAllLogin | all user cnt = %d", onlineList.size());

    userOnlineListCmd cmd;
    TaskPtr task  = Task::makeTask(cmd);
    task->m_from = TASK_SERVER;

    m_userManager_->addToAllUser(task);
}

bool CSourceEng::isUserExistByAccount(const std::string &account)
{
    UserPtr user = m_userManager_->findUser(account);

    if(!user) return false;
    return true;
}

void CSourceEng::recordChat(UserPtr user, const std::string &content)
{
    m_chatRecord.record(user, content);
}

void CSourceEng::chatRecordToDB()
{
    BOOST_LOG_TRIVIAL(info) << "服务器关闭处理聊天数据";
    m_chatRecord.writeToDb();
}
