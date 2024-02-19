//
// Created by wenheng on 23年9月23日.
//

#include "TCP_Server.h"
#include "../common/CSourceEng.h"
#include "../common/comm_func.h"

#include "csignal"
#include "boost/json.hpp"

void TCP_Server::run()
{
    SessionPtr session(new Session(m_io));

    using namespace boost::asio::placeholders;

    m_acceptor.async_accept(session->m_fd, boost::bind(&TCP_Server::handle_accept, this, \
        session, boost::asio::placeholders::error));

}

void TCP_Server::handle_accept(SessionPtr session, error_code_type ec)
{
    if(ec)
    {
//        BOOST_LOG_TRIVIAL(warning) << (boost::format("session[%1%] 连接失败 | error = %2%") %session->m_uuid_  %ec.what()).str();
        BOOST_LOG_TRIVIAL(error) << commfunc::getFormatStr("handle_accept session[%1%] 连接失败 | error = %2%", session->m_uuid_, ec.message());
        return;
    }

    auto ed = session->m_fd.remote_endpoint();

//    BOOST_LOG_TRIVIAL(info) << (boost::format("session[%1%] 已连接 | ip = %2%, port = %3%") %)

    if(session->checkLogin())
    {
        BOOST_LOG_TRIVIAL(info) << commfunc::getFormatStr("session[%1%] 已连接成功 | ip = %2%, port = %3%", \
        session->m_uuid_, ed.address().to_string(), ed.port());

        CSourceEng::getMe()->m_SessionManager_.m_waitConnectSessions.push(session);
    }

    run();
//    m_Sessions_.push(session);
}

void TCP_Server::init(ip::tcp::endpoint ed)
{
    m_acceptor = boost::asio::ip::tcp::acceptor(m_io, ed);
    run();
    CSourceEng::getMe()->stratup();
}

TCP_Server::~TCP_Server()
{
    BOOST_LOG_TRIVIAL(info) << commfunc::getFormatStr("服务器关闭!!!!!");
}

void TCP_Server::handle_close(int signalvalue)
{
    BOOST_LOG_TRIVIAL(error) << commfunc::getFormatStr("TCP_Server | 收到信号: [%d]", signalvalue);
    boost::system::error_code ec;
    m_acceptor.close(ec);
    CSourceEng::getMe()->m_SessionManager_.closeAll();
    CSourceEng::getMe()->chatRecordToDB();
    if(ec)
    {
        BOOST_LOG_TRIVIAL(error) << commfunc::getFormatStr("TCP_Server | 监听器关闭 %s", ec.message());
    }
}
