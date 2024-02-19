//
// Created by wenheng on 23-5-2.
//

#ifndef BOOST_ASIO_NEW_COMMONCLASS_H
#define BOOST_ASIO_NEW_COMMONCLASS_H

#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/format.hpp"

#include "functional"
#include "iostream"

#include "QDebug"

typedef boost::system::error_code error_code_type;


class time_with_func
{
    typedef void(handlder_type)(error_code_type ec);

public:
    time_with_func(boost::asio::io_service& ioService, std::function<void()> func, std::chrono::seconds sec, int maxCnt = -1) : m_cnt(0), m_maxCnt(maxCnt)\
    , m_func(func), m_timer(ioService, sec), m_sec(sec), isRunning(true)
    {
//        m_timer.async_wait(boost::bind(&time_with_func::handler, this, boost::asio::placeholders::error));
    }

    time_with_func(boost::asio::io_service& ioService) : m_cnt(0), m_maxCnt(1), m_timer(ioService), m_sec(std::chrono::seconds(1)), isRunning(true)
    {

    }

    void start()
    {
        isRunning = true;
        m_timer.async_wait(boost::bind(&time_with_func::handler, this, boost::asio::placeholders::error));
    }

    void close()
    {
        error_code_type ec;
        m_timer.cancel(ec);
        isRunning = false;
        if(ec)
            std::cerr << boost::format("timer close error | %s") % ec.message() << std::endl;
    }

    void start(std::function<void()> func, std::chrono::seconds sec, int maxCnt)
    {
        m_sec = sec;
        m_maxCnt = maxCnt;
        m_func = func;

        start();
    }

private:

    int m_cnt;
    int m_maxCnt;
    std::function<void()> m_func;
    boost::asio::steady_timer m_timer;
    std::chrono::seconds m_sec;
    bool isRunning;

    void handler(const boost::system::error_code& ec)
    {

        if(ec)
        {
            qWarning() << "timer handler error  | " << QString(ec.message().c_str());
            return;
        }
//        qDebug() << "timer handler start successfully~~~";
        if(m_maxCnt != -1)
        {
            if(m_cnt++ > m_maxCnt)
            {
                qWarning() << "m_cnt++ > m_maxCnt | m_cnt = " << m_cnt << " m_maxCnt = " << m_maxCnt;
                return;
            }
        }

        if(!m_func || !isRunning)
        {
            if(!m_func)
            {
                qWarning() << "m_func is null";
            }

            if(!isRunning)
            {
                qWarning() << "isRunning status is false";
            }
            return;
        }

        m_func();

        m_timer.expires_from_now(m_sec);

        m_timer.async_wait(boost::bind(&time_with_func::handler, this, boost::asio::placeholders::error));
    }

};

#endif //BOOST_ASIO_NEW_COMMONCLASS_H
