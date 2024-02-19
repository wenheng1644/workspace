//
// Created by wenheng on 23年10月19日.
//

#include "user.h"

#include "../common/CSourceEng.h"
#include "../common/comm_func.h"


#include "../netResolver/base_cmd.h"
#include "../netResolver/user_cmd.h"
#include "../netResolver/sys_cmd.h"

user::user(SessionPtr session, std::shared_ptr<userManager> userManager) : m_sex_(robot), m_dailyOnlineTimes(0), m_lastLoginTimeZone(0), m_gmlevel(0),m_onylyId(boost::uuids::random_generator()()),\
    m_connecthandle(session), m_isOnline(true), m_name(""), m_userManager(userManager)
{

}

bool user::isVaild()
{
    std::shared_lock<std::shared_mutex> gl(m_mutex);
    return isVaildWithNoMutex();
}

bool user::isVaildWithNoMutex()
{
    if(m_connecthandle.lock()) return true;
    return false;
}

void user::hanldeTask()
{
    SessionPtr session = m_connecthandle.lock();

    if(!session) return;
    std::deque<TaskPtr> queue;

    {
        std::shared_lock<std::shared_mutex> gl(m_mutex);
        session->swapTasks(queue);
    }


    for(TaskPtr task : queue)
    {
        //TO DO

        netMsgPtr data = task->m_msg;
        //业务层解包处理逻辑(聊天包)
        if(data->head.type == 1 && data->head.subtype == 2)
        {
            netData serData = std::make_pair(data->body, data->head.len);
            userChatCmd cmd = netQtResolver::getCmdByNetData<userChatCmd>(serData);
//            cmd.m_time = time(nullptr);

            auto net = netQtResolver::getNetDataByCmd(cmd);
            netMsg msg(data->head.type, data->head.subtype, net);
            *(task->m_msg) = msg;

            BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("hanldeTask | (user[%1%], gmlv = %2%, sex = %3%, sendtime = %4%) 读取聊天消息 = %5%", \
            m_name, (int)m_gmlevel, (int)m_sex_, cmd.m_time ,cmd.m_content);

            netData serSendStr = netQtResolver::getSerializeStrByNet(*data);

            session->send(task);

            if(task->m_from == TASK_CLIENT && isMe(task->m_ownerid))
                CSourceEng::getMe()->recordChat(shared_from_this(), cmd.m_content);
        }

        //查看在线人数
        if(data->head.type == 1 && data->head.subtype == 3)
        {
            netData serData = std::make_pair(data->body, data->head.len);
            userCheckOnlineCmd cmd = netQtResolver::getCmdByNetData<userCheckOnlineCmd>(serData);

            auto userManager = m_userManager.lock();
            if(userManager)
            {
                cmd.m_onlineCnt = userManager->onlineCnt();
                BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("hanldeTask | (user[%1%], gmlv = %2%, sex = %3%) 请求当前在线人数 = %4%", \
                    m_name, (int)m_gmlevel, (int)m_sex_, cmd.m_onlineCnt);
            }

            auto net = netQtResolver::getNetDataByCmd(cmd);
            netMsg msg(data->head.type, data->head.subtype, net);
            *(task->m_msg) = msg;

            session->send(task);
        }

        if(data->head.type == USERSYS && data->head.subtype == USERSYS_ONLINELIST)
        {
            netData serData = std::make_pair(data->body, data->head.len);
            userOnlineListCmd cmd = netQtResolver::getCmdByNetData<userOnlineListCmd>(serData);

            auto userManager = m_userManager.lock();
            if(userManager)
            {
                auto onlineList = userManager->getOnlineUserList();

                size_t cnt = onlineList.size();
                for(const auto& v : onlineList)
                {
                    userData data;
                    data.m_gmlevel = v->m_gmlevel;
                    data.name = v->m_name;
                    data.sex = v->sex();

                    cmd.m_userList.push_back(data);
                }

                BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("hanldeTask | (user[%1%], gmlv = %2%, sex = %3%) 请求当前在线列表 = %4%", \
                    m_name, (int)m_gmlevel, (int)m_sex_, cnt);

//                auto net = netQtResolver::getNetDataByCmd(cmd);
//                netMsg msg(data->head.type, data->head.subtype, net);
//                *(task->m_msg) = msg;
                TaskPtr task1 = Task::makeTask(cmd);
                BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("hanldeTask | 请求在线列表, type = %d, subtype = %d", (int)task1->m_msg->head.type,\
                    (int)task1->m_msg->head.subtype);
                session->send(task1);
            }
        }

    }

}

bool user::operator==(const user &other)
{
    if(m_onylyId == other.m_onylyId) return true;
    return false;
}

bool user::operator==(SessionPtr session)
{
    if(m_connecthandle.lock() && session->m_uuid_ == m_connecthandle.lock()->m_uuid_) return true;
    return false;
}

void user::addTask(TaskPtr task)
{
    std::shared_lock<std::shared_mutex> gl(m_mutex);
    SessionPtr  session = m_connecthandle.lock();

    if(!session) return;

    session->read(task);
}

void user::online(bool status)
{
    std::unique_lock<std::shared_mutex> uniqueLock(m_mutex);
    m_isOnline = status;
}

bool user::online()
{
    std::shared_lock<std::shared_mutex> sharedLock(m_mutex);
    return m_isOnline;
}

void user::init_userData(const userData &data)
{
    std::unique_lock<std::shared_mutex> uniqueLock(m_mutex);
    m_gmlevel = data.m_gmlevel;
    m_name = data.name;
    m_sex_ = data.sex;
}

bool user::isMe(boost::uuids::uuid sessionid)
{
    auto session = m_connecthandle.lock();
    if(!session) return false;

    return session->m_uuid_ == sessionid;
}

void userManager::run()
{
    for(auto user : m_users)
    {
        user->hanldeTask();
    }
}

void userManager::remove(SessionPtr session)
{
    std::unique_lock<std::shared_mutex> uniqueLock(m_users.m_mutex_);

    auto findIter = m_users.end();
    for(auto iter = m_users.begin(); iter != m_users.end(); ++iter)
    {
        if(**iter == session)
        {
            findIter = iter;
            break;
        }
    }

    if(findIter == m_users.end()) return;
    BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("user sex = [%d] 退出", (int)(*findIter)->sex());
    uniqueLock.unlock();
    m_users.remove(*findIter);
}

void userManager::push(UserPtr user)
{
    m_users.push(user);
}

void userManager::addToAllUser(TaskPtr task)
{
    std::unique_lock<std::shared_mutex> uniqueLock(m_users.m_mutex_);
    for(auto& user : m_users)
        user->addTask(task);
}

void userManager::remove(UserPtr user)
{
    std::unique_lock<std::shared_mutex> uniqueLock(m_users.m_mutex_);
    auto findIter = m_users.end();
    for(auto iter = m_users.begin(); iter != m_users.end(); ++iter)
    {
        if(**iter == *user)
        {
            findIter = iter;
            break;
        }
    }

    if(findIter == m_users.end()) return;
    BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("user[%s] sex = [%d] 退出", (*findIter)->name(), (int)(*findIter)->sex());
    uniqueLock.unlock();
    m_users.remove(*findIter);
}

UserPtr userManager::findUser(SessionPtr session)
{
    if(!session)
    {
        BOOST_LOG_TRIVIAL(warning) << commfunc::getFormatStr("userManager::findUser | 查找session指针无效");
        return UserPtr();
    }
    std::unique_lock<std::shared_mutex> uniqueLock(m_users.m_mutex_);

    UserPtr findUser = findUserWithNoMutex(session);

    return findUser;
}

UserPtr userManager::findUser(const std::string &account)
{
    std::unique_lock<std::shared_mutex> uniqueLock(m_users.m_mutex_);
    UserPtr findUser = findUserWithNoMutex(account);
    return findUser;
}

UserPtr userManager::findUserWithNoMutex(SessionPtr session)
{
    if(!session) return UserPtr();
    for(auto iter = m_users.begin(); iter != m_users.end(); ++iter)
    {
        if(**iter == session)
            return *iter;
    }
    return UserPtr();
}
UserPtr userManager::findUserWithNoMutex(const std::string &account)
{
    if(account.empty()) return UserPtr();

    for(auto iter = m_users.begin(); iter != m_users.end(); ++iter)
    {
        if((*iter)->name() == account)
            return *iter;
    }
    return UserPtr();
}


size_t userManager::onlineCnt()
{
    return m_users.size();
}

std::vector<UserPtr> userManager::getOnlineUserList()
{
    std::vector<UserPtr> onlineList;
    {
        std::shared_lock<std::shared_mutex> sharedLock(m_users.m_mutex_);
//        onlineList.resize(m_users.size());
        for(auto iter = m_users.begin(); iter != m_users.end(); ++iter)
        {
            onlineList.push_back(*iter);
        }
    }

    return onlineList;
}




