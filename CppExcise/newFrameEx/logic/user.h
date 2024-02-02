#ifndef USER
#define USER

#include "string"
#include "deque"

#include "../netcomm/netcommhead.h"
#include "../comm/commhead.h"
#include "../server/TCPConnection.h"

enum Sex
{
    male = 1,
    female = 2,
};

//账号属性
struct userComm
{
    std::string name;
    std::string account;
    u_char      age;
    Sex         sex;
};

class user
{
public:
    user() = default;
    user(const userComm& comm, TCPConnection_ptr conn);

    virtual ~user() = default;

    void push_netMsg(netMsg_ptr msg);
    void run();

    void onChatContentMessage(cmd::chatMessageCmd* msg);

protected:
    std::string m_name;
    std::string m_account;
    u_char      m_age;
    Sex         m_sex;

    std::mutex m_commMutex;             //通用锁

    std::mutex m_msgListMutex;          //消息队列锁
    std::deque<netMsg_ptr> m_msgLists;  //待处理消息队列

    std::weak_ptr<TCPConnection> m_wTcpConn;    //句柄

private:
};

typedef std::shared_ptr<user> user_ptr;

#endif