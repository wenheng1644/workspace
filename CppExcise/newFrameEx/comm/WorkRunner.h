#ifndef WORKRUNNER
#define WORKRUNNER

#include "commhead.h"
#include "../server/commServer.h"

#include "functional"

#include "boost/thread.hpp"
#include "boost/noncopyable.hpp"

class WorkRunner : public boost::noncopyable
{
public:
    WorkRunner();


    ~WorkRunner() = default;

    bool start(size_t num);

    ioserver_tp& get_io() { return m_io;}

    size_t get_curthreadsize() { return m_theadgroup.size();}
    //投递任务
    void post(std::function<void()>);

private:
    ioserver_tp m_io;
    ioserver_tp::work m_work;
    boost::thread_group m_theadgroup;
    size_t m_threadnum;

};



#endif