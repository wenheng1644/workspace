//
// Created by wenheng on 23年11月11日.
//

#include "boost/format.hpp"

#include "chatRecordManager.h"

#include "../common/CSourceEng.h"
#include "../common/comm_func.h"



#define CREATEDBCONN(conn) boost::asio::io_context ctx;\
                        boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::tls_client); \
                        conn = std::make_shared<MySqlConn>(ctx, ssl_ctx);

typedef std::shared_ptr<MySqlConn> MySqlConnPtr;


struct chatRecordSQL
{
    u_int64_t id;
    std::string account;
    std::uint64_t sendtime;
    std::string content;
};

BOOST_DESCRIBE_STRUCT(chatRecordSQL, (), (id, account, sendtime, content))


chatRecordManager::chatRecordManager()
{
    init();
}



void chatRecordManager::init()
{
//    boost::asio::io_context ctx;
//    boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::tls_client);
//    MySqlConn conn(ctx, ssl_ctx);
    MySqlConnPtr conn;
//    conn1 = std::make_shared<MySqlConn>(ctx, ssl_ctx);
    CREATEDBCONN(conn)

    boost::mysql::handshake_params params("root", "xwz111598", "test_db");

    if(!conn->connect("127.0.0.1", 3306,params)) return;

    boost::format f = boost::format("select * from chatRecord");
    boost::mysql::static_results<chatRecordSQL> result;

    conn->excute(f.str().c_str(), result);

    if(result.rows().empty())
    {
        BOOST_LOG_TRIVIAL(info) << "聊天数据库表无内容";
        return;
    }

    for(auto& v : result.rows())
    {
        chatRecordPtr data(new chatRecord);
        data->content = v.content;
        data->sendtime = v.sendtime;
        data->account = v.account;

        m_curChatRecords.push(data);
    }

    BOOST_LOG_TRIVIAL(info) << commfunc::getFormatStr("读取数据库聊天消息%d条", result.rows().size());
}

void chatRecordManager::record(UserPtr user, const std::string &content)
{
    chatRecordPtr data(new chatRecord);
    data->content = content;
    data->account = user->name();
    data->sendtime = time(nullptr);

    m_curChatRecords.push(data);
    m_waitToAddLists.push(data);

    BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("chatRecordManager::record | account[%s]记录聊天数据: %s, m_waitToAddLists 的数量: %d", \
        user->name(), content, m_waitToAddLists.size());
}

void chatRecordManager::writeToDb()
{
    MySqlConnPtr conn;
    CREATEDBCONN(conn);

    if(!conn)
    {
        BOOST_LOG_TRIVIAL(warning) << "writeToDb | conn 创建失败";
        return;
    }

    boost::mysql::handshake_params params("root", "xwz111598", "test_db");

    if(!conn->connect("127.0.0.1", 3306,params))
    {
        BOOST_LOG_TRIVIAL(warning) << "writeToDb | 数据库句柄连接失败...";
        return;
    }


    BOOST_LOG_TRIVIAL(info) << "writeToDb | 聊天数据开始插入数据库";
    bool isOk = true;
    int cnt = 0;
    for(const auto& data : m_waitToAddLists)
    {
        boost::format f = boost::format("insert into chatRecord (account, sendtime, content) values('%s', %d, '%s')")\
            % data->account % data->sendtime % data->content;

        if(!conn->excute_noReturn(f.str().c_str()))
        {
            BOOST_LOG_TRIVIAL(warning) << commfunc::getFormatStr("插入数据库错误, %s", f.str());
            isOk = false;
            break;
        }
        cnt++;
    }

    if(isOk)
    {
        if(cnt > 0) BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("聊天数据全部插入成功, 总共%d条记录!!!", cnt);
        else BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("没有聊天数据可插入数据库~~~");
    }


}

void chatRecordManager::onUserLogin(UserPtr user)
{
    if(!user) return;
    for (const auto& data : m_curChatRecords)
    {
        userChatCmd cmd;
        cmd.m_name = data->account;
        cmd.m_sex = 0;
        cmd.m_content = data->content;
        cmd.m_time = data->sendtime;

        TaskPtr task = Task::makeTask(cmd);
        task->m_from = TASK_SERVER;
        user->addTask(task);
    }
}

void chatRecordManager::setUserManager(std::shared_ptr<userManager> userManagerObj)
{
    m_userManager = userManagerObj;
}



