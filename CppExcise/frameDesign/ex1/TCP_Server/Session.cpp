//
// Created by wenheng on 23年9月23日.
//

#include "Session.h"

#include "../common/CSourceEng.h"
#include "../common/comm_func.h"

#include "../netResolver/base_cmd.h"
#include "../netResolver/user_cmd.h"
#include "../netResolver/sys_cmd.h"

#include "../../../mysqlEx/MySqlConn.h"

#include <boost/describe/class.hpp>

struct userField
{
    u_int64_t onlyid;
    std::string account;
    u_char sex;
    u_char age;
    std::string password;
};

BOOST_DESCRIBE_STRUCT(userField, (), (onlyid, account, sex, age, password))

Session::Session(boost::asio::io_service &io) : m_fd(io), m_uuid_(boost::uuids::random_generator()()),\
        m_lastUpDateTimeZone(std::time(nullptr)), m_timer_(io){}


void Session::send(const std::string &ser_str, size_t len)
{
    if(ser_str.empty()) return;
    if(!m_fd.is_open())
    {
        BOOST_LOG_TRIVIAL(error) << commfunc::getFormatStr(" Session::send | session[%1%] socket失效", \
            m_uuid_);
        m_timer_.close();
        CSourceEng::getMe()->m_SessionManager_.m_waitDisConnectSessions.push(shared_from_this());
        CSourceEng::getMe()->m_SessionManager_.m_waitDisConnectSessions.m_cond_.notify_one();
        return;
    }

    update_heartBeat();
    BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("发包打印11111111");
    m_fd.async_send(boost::asio::buffer(ser_str, len), boost::bind(&Session::handle_send, shared_from_this(), \
        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void Session::handle_send(error_code_type ec, size_t bytes)
{
    if(ec)
    {
        std::cerr << boost::format("(uuid = %1%) error msg = %s, bytes = %d") % m_uuid_ % ec.message() % bytes << std::endl;
        return;
    }
    BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("发包打印22222222");
}

bool Session::isVaild()
{
    error_code_type  ec;
    m_fd.remote_endpoint(ec);

    if(!m_fd.is_open())
        return false;

    if(ec)
    {
//        std::cerr << boost::format("session[%1%] error： %2%") % m_uuid_ % ec.what() << std::endl;
        return false;
    }

    return true;
}

void Session::run()
{
    netMsgPtr data(new netMsg);

//    std::cout << boost::format("Session[%1%]: threadid = %2%, sizeof(netHead) = %3%") % m_uuid_ % std::this_thread::get_id() \
//        % sizeof(netHead) << std::endl;
    using namespace boost::asio::placeholders;

    m_fd.async_read_some(boost::asio::buffer((char*)&(data->head), sizeof(netHead)), boost::bind(&Session::handle_readhead, shared_from_this(), \
        data, error, bytes_transferred));
}

void Session::handle_readhead(netMsgPtr data, error_code_type ec, size_t bytes)
{
    if(ec || bytes == 0)
    {
        BOOST_LOG_TRIVIAL(error) << commfunc::getFormatStr(" handle_readhead | session[%1%] 连接断开, error = %2%", \
            m_uuid_, ec.message());

        close();
        return;
    }

//    std::cout << boost::format("handle_readhead111 | session[%1%] -- threadId = %2%, headbytes = %3% bodybytes = %4%") % m_uuid_ % std::this_thread::get_id() \
//        %bytes  %data->head.len << std::endl;

    using namespace boost::asio::placeholders;
    data->body.resize(data->head.len, 0);
    m_fd.async_read_some(boost::asio::buffer((data->body), data->head.len), boost::bind(&Session::handle_readbody, shared_from_this(), \
        data, error, bytes_transferred));


}

void Session::handle_readbody(netMsgPtr data, error_code_type ec, size_t bytes)
{
    if(ec)
    {
        BOOST_LOG_TRIVIAL(error) << commfunc::getFormatStr("handle_readbody | session[%1%] 连接断开, error = %2%", \
            m_uuid_, ec.message());
        return;
    }

    TaskPtr task(new Task(m_uuid_, *data));
    if(data->head.type == 1 && data->head.subtype == 2)
    {
        CSourceEng::getMe()->addToAllUser(task);
    }
    else
    {
        m_netTask_.push(task);
    }

//    read(task);
    if (!handle_sendHeartBeat(data->head.type, data->head.subtype))
    {
        //TO--DO
    }
    BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("handle_readbody | 查看收包回调信息");
    update_heartBeat();
    run();
}

bool Session::operator==(const Session &other)
{
    if(m_uuid_ == other.m_uuid_) return true;
    return false;
}

void Session::handle_checkHeartBeat()
{
    time_t  now = std::time(nullptr);

    if(now - m_lastUpDateTimeZone >= 10 && isVaild())
    {
        BOOST_LOG_TRIVIAL(warning) << commfunc::getFormatStr("handle_checkHeartBeat | 心跳包超时: before = %d, now = %d, diff = %d", \
            m_lastUpDateTimeZone, now, now - m_lastUpDateTimeZone);

        m_fd.close();
        CSourceEng::getMe()->m_SessionManager_.m_waitDisConnectSessions.push(shared_from_this());
        CSourceEng::getMe()->m_SessionManager_.m_waitDisConnectSessions.m_cond_.notify_one();
    }
}

void Session::update_heartBeat()
{
    m_lastUpDateTimeZone = std::time(nullptr);
//    BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("handle_sendHeartBeat | 更新心跳包");
}

bool Session::handle_sendHeartBeat(u_char type, u_char subtype)
{
    if(type != SYSTEM || subtype != SYSTEM_HEARTBEAT) return false;
    if(!isVaild())
    {
        BOOST_LOG_TRIVIAL(warning) << commfunc::getFormatStr("handle_sendHeartBeat | session[%1%] 状态失效", \
            m_uuid_);
        return false;
    }
    systemHeartBeatCmd cmd;
    cmd.m_time = std::time(nullptr);
    cmd.state = 100;

    auto net = netQtResolver::getNetDataByCmd(cmd);
    netMsg msg(SYSTEM, SYSTEM_HEARTBEAT, net);

//    netData serStr = netQtResolver::getSerializeStrByNet(msg);

//    size_t bytes = m_fd.write_some(boost::asio::buffer(serStr.first, serStr.second));
    TaskPtr task(new Task(m_uuid_, msg));
    send(task);

    update_heartBeat();
//    std::cout << boost::format("handle_sendHeartBeat | send heartbeat bytes = %d") % bytes << std::endl;
//    BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("handle_sendHeartBeat | 心跳包刷新");
    return true;
}

void Session::startTimer()
{
    m_timer_.start(std::bind(&Session::handle_checkHeartBeat, this), std::chrono::seconds(5),-1);
}

void Session::swapTasks(std::deque<TaskPtr> &queue)
{
    m_netTask_.getDatas(queue);
}

void Session::sendDataPacks()
{
    while(!m_SendTask_.empty())
    {
//        BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("send Pack |session = %1% before --> size = %2%", m_uuid_, m_SendTask_.size());
        TaskPtr task = m_SendTask_.pop();
        netMsgPtr data = task->m_msg;

        netData sendStr = netQtResolver::getSerializeStrByNet(*data);
        BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("send Pack |session = %1% after --> size = %2%, type = %3%, subtype = %4%", m_uuid_,\
            m_SendTask_.size(), (int)data->head.type, (int)data->head.subtype);
        send(sendStr.first, sendStr.second);
    }
}

void Session::send(TaskPtr task)
{
    m_SendTask_.push(task);
}

void Session::read(TaskPtr task)
{
    m_netTask_.push(task);
}

bool Session::checkLogin()
{
    netMsg msg;
    error_code_type  ec1;
    m_fd.read_some(boost::asio::buffer(&msg.head,sizeof(netHead)), ec1);
    if(ec1) return false;

    error_code_type ec2;
    msg.body.resize(msg.head.len, 0);
    m_fd.read_some(boost::asio::buffer(msg.body, msg.head.len), ec2);

    if(ec2) return false;

    netData serData = std::make_pair(msg.body, msg.head.len);
    userLoginCmd loginCmd = netQtResolver::getCmdByNetData<userLoginCmd>(serData);

    boost::asio::io_context ctx;
    boost::asio::ssl::context ssl_ctx(boost::asio::ssl::context::tls_client);
    MySqlConn conn(ctx, ssl_ctx);
    boost::mysql::handshake_params params("root", "xwz111598", "test_db");

    LoginStatusType status = DATABASE_CONNECTERROR;
    loginCmd.m_status = status;

    if(conn.connect("127.0.0.1", 3306,params))
    {
        status = SUCCESS;

        boost::format f = boost::format("select * from user where account='%s'") % loginCmd.m_account;
        boost::mysql::static_results<userField> result;
        BOOST_LOG_TRIVIAL(info) << commfunc::getFormatStr("sql statment = %s", f.str());
        if(!conn.excute(f.str().c_str(), result))
        {
            status = DATABASE_EXCUTEERROR;
            BOOST_LOG_TRIVIAL(warning) << commfunc::getFormatStr("数据库执行失败");
        }

        if(status == SUCCESS)
        {
            if(loginCmd.m_login_operation == TO_LOGIN)
            {
                if(result.rows().empty())
                {
                    status = No_ACCOUNT;
                    BOOST_LOG_TRIVIAL(warning) << commfunc::getFormatStr("数据库没有对应账号");
                }
                if(status == SUCCESS && CSourceEng::getMe()->isUserExistByAccount(loginCmd.m_account))
                {
                    status = ERROR_ONLINE;
                    BOOST_LOG_TRIVIAL(warning) << commfunc::getFormatStr("账号[%s]已在线", loginCmd.m_account);
                }

                if(status == SUCCESS)
                {
                    userField data = result.rows()[0];

                    if(data.password != loginCmd.m_password)
                    {
                        status = ERROR_PASSWORD;
                        BOOST_LOG_TRIVIAL(warning) << commfunc::getFormatStr("密码错误");
                    }
                }
            }

            if(loginCmd.m_login_operation == TO_REGISTER)
            {
                if(!result.rows().empty())
                {
                    status = REGISTER_HAD_ACCOUNT;
                    BOOST_LOG_TRIVIAL(warning) << commfunc::getFormatStr("注册失败，数据库已有账号");
                }
                boost::format insert_str = boost::format("insert into user (account, sex, age, password) values('%s',%d,0,'%s')") % loginCmd.m_account \
                    %(int)loginCmd.m_sex % loginCmd.m_password;

                if(status == SUCCESS && !conn.excute_noReturn(insert_str.str().c_str()))
                {
                    status = DATABASE_EXCUTEERROR;
                    BOOST_LOG_TRIVIAL(warning) << commfunc::getFormatStr("注册失败，插入数据库操作有误");
                }

                if(status == SUCCESS)
                    BOOST_LOG_TRIVIAL(info) << commfunc::getFormatStr("注册成功, (%s, %s)", loginCmd.m_account, loginCmd.m_password);
            }
        }
    }
    else
    {
        BOOST_LOG_TRIVIAL(warning) << commfunc::getFormatStr("数据库连接失败");
    }
    loginCmd.m_status = status;
    netData sendLoginData = netQtResolver::getNetDataByCmd(loginCmd);
    netMsgPtr loginMsg(new netMsg(USERSYS, USERSYS_LOGIN, sendLoginData));
//    TaskPtr task(new Task(m_uuid_, loginMsg));

    netData sendAllData = netQtResolver::getSerializeStrByNet(*loginMsg);
    m_fd.write_some(boost::asio::buffer(sendAllData.first, sendAllData.second));
//    send(task);

    BOOST_LOG_TRIVIAL(debug) << commfunc::getFormatStr("account = %1%, password = %2%", loginCmd.m_account, loginCmd.m_password);
    userData data;
    data.sex = loginCmd.m_sex == 0 ? man : lady;
    data.name = loginCmd.m_account;
    data.m_gmlevel = 5;

    m_userData = data;

    return status == SUCCESS;
}

void Session::close()
{
//    if(!isVaild())
//    {
//        BOOST_LOG_TRIVIAL(warning) << commfunc::getFormatStr("Session::close | session 句柄關閉失敗...");
//        return;
//    }

    m_fd.close();
    m_timer_.close();
    CSourceEng::getMe()->m_SessionManager_.m_waitDisConnectSessions.push(shared_from_this());
    CSourceEng::getMe()->m_SessionManager_.m_waitDisConnectSessions.m_cond_.notify_all();
}


void SessionManager::handle_SendPackData()
{
    for(SessionPtr session : m_onlineSessions)
    {
        session->sendDataPacks();
    }


}

void SessionManager::closeAll()
{
    for(SessionPtr session : m_onlineSessions)
    {
        session->close();
    }
}
