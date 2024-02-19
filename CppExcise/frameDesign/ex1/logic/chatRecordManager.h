//
// Created by wenheng on 23年11月11日.
//

#ifndef EX1_CHATRECORDMANAGER_H
#define EX1_CHATRECORDMANAGER_H

#include "boost/json.hpp"
#include "../common/threadSafe_Container.h"

#include "../../../mysqlEx/MySqlConn.h"

#include <boost/describe/class.hpp>
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"

#include "../logic/user.h"

struct chatRecord
{
    std::string account;
    u_int64_t sendtime;
    std::string content;
    boost::uuids::uuid onlyid;
    chatRecord() : onlyid(boost::uuids::random_generator()()) {}

    chatRecord(const chatRecord& other) : sendtime(other.sendtime), account(other.account), content(other.content), onlyid(other.onlyid) {}

    bool operator==(const chatRecord& other)
    {
        return onlyid == other.onlyid;
    }

    bool operator!=(const chatRecord& other)
    {
        return !(*this == other);
    }

};

typedef std::shared_ptr<chatRecord> chatRecordPtr;


//class userManager;
class chatRecordManager {
public:
    chatRecordManager();

    void setUserManager(std::shared_ptr<userManager> userManagerObj);
    void record(UserPtr user, const std::string& content);

    void onUserLogin(UserPtr user);

    void writeToDb();
private:
    threadSafe_Container<chatRecord> m_curChatRecords;
    threadSafe_Container<chatRecord> m_waitToAddLists;

    void init();

    std::weak_ptr<userManager> m_userManager;
};


#endif //EX1_CHATRECORDMANAGER_H
