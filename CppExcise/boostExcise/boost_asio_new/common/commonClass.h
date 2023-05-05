//
// Created by wenheng on 23-5-2.
//

#ifndef BOOST_ASIO_NEW_COMMONCLASS_H
#define BOOST_ASIO_NEW_COMMONCLASS_H

#define LUASCRIPTFILE "../luaScript/main.lua"

#include "deque"

#include "functional"
#include "boost/timer.hpp"
#include "boost/asio.hpp"
#include "boost/bind.hpp"

#include "../netMsg/netMsg.h"

typedef std::deque<netMsg> netMsgList;
typedef boost::system::error_code error_code_type;


class Singleton
{
public:
    static Singleton* getSingleton() {
        if(!m_signleton)
            m_signleton = new Singleton();
        return m_signleton;
    }

    virtual ~Singleton(){
        if(m_signleton)
            delete m_signleton;
    }
protected:
    Singleton() = default;
private:
    static Singleton* m_signleton;
};

class time_with_func
{
    typedef void(handlder_type)(error_code_type ec);

public:
    time_with_func(boost::asio::io_service& ioService, std::function<void()> func, std::chrono::seconds sec, int maxCnt = -1) : m_cnt(0), m_maxCnt(maxCnt)\
    , m_func(func), m_timer(ioService, sec), m_sec(sec)
    {
//        m_timer.async_wait(boost::bind(&time_with_func::handler, this, boost::asio::placeholders::error));
    }

    time_with_func(boost::asio::io_service& ioService) : m_cnt(0), m_maxCnt(1), m_timer(ioService), m_sec(std::chrono::seconds(1))
    {

    }

    void start()
    {
        m_timer.async_wait(boost::bind(&time_with_func::handler, this, boost::asio::placeholders::error));
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

    void handler(const boost::system::error_code&)
    {
        if(m_maxCnt != -1)
        {
            if(m_cnt++ > m_maxCnt) return;
        }

        if(!m_func) return;

        m_func();

        m_timer.expires_from_now(m_sec);

        m_timer.async_wait(boost::bind(&time_with_func::handler, this, boost::asio::placeholders::error));
    }

};

#endif //BOOST_ASIO_NEW_COMMONCLASS_H
