//
// Created by wenheng on 23-6-20.
//

#include "netserver.h"

#include "boost/format.hpp"
#include "boost/bind.hpp"

#include "../logic/UserEng.h"

void netserver::loop() {

    using boost::format;
    while(true)
    {
//        std::cout << format("loop | m_cmdQueue.size = %d") % m_cmdQueue.size() << std::endl;

        //此处要加互斥锁
        std::lock_guard<std::mutex> g(m_cmdMutex);
        if(!m_userCmds.empty())
        {

            for(auto iter = m_userCmds.begin(); iter != m_userCmds.end(); iter++)
            {
                cmdQueue queue = iter->second;
                while(!queue.empty())
                {
                    bCmd* cmd = queue.front();

                    netSessionPtr p = getNetSessionByOnlyid(iter->first);
                    if(p)
                    {
                        p->operate(cmd);
                    }

                    queue.pop();
                }
            }
        }
    }

}

netserver::netserver(boost::asio::io_service &ioserver, tcp::endpoint ed) :
        m_ioserver(ioserver), m_accpter(ioserver, ed)
{
    std::thread t1(&netserver::loop, this);
    t1.detach();
}

//服务器运行
void netserver::run()
{
//    std::shared_ptr<tcp::socket> f(new tcp::socket(m_ioserver));
    std::shared_ptr<netSession> session(new netSession(m_ioserver));


    m_accpter.async_accept(session->socket(), boost::bind(&netserver::handle_accpet, this, session, boost::asio::placeholders::error));
//    run();
}

void netserver::handle_accpet(netSessionPtr session, error_code_type ec)
{
    using boost::format;
    if(ec)
    {
        std::cout << format("ec : %s") % ec.what() << std::endl;
        session->close();
        return;
    }

//    {
//        std::lock_guard<std::mutex> g(m_cmdMutex);
//        cmdQueue queue;
//        m_userCmds[session->m_onlyid] = queue;
//
//        m_sessions.push_back(session);
//    }

    char buff[1024] = {0};
    bCmd* cmd = new bCmd;
    session->socket().async_read_some(boost::asio::buffer(cmd, sizeof(bCmd)), \
        boost::bind(&netserver::handle_readhead, this, session, cmd, boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));

    run();
}

void netserver::handle_readhead(netSessionPtr session, bCmd* cmd, error_code_type ec, size_t bytes)
{
    using boost::format;
    if(ec)
    {
        std::cerr << format("error = %s") %ec.what() << std::endl;
        session->close();
        return;
    }
    if(!cmd)
    {
        std::cerr << format("cmd is empty") << std::endl;
//        session->close();
        return;
    }

    char buff[1024] = {0};
    session->socket().async_read_some(boost::asio::buffer(buff, cmd->len))
}

bool netserver::isEsixtSessionByOnlyid(size_t onlyid)
{
    for(auto session : m_sessions)
    {
        if(session->m_onlyid == onlyid)
            return true;
    }
    return false;
}

netSessionPtr netserver::getNetSessionByOnlyid(size_t onlyid) {
    for(auto& session : m_sessions)
    {
        if(session->m_onlyid == onlyid)
            return session;
    }
}
