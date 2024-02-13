#include "WorkRunner.h"

WorkRunner::WorkRunner() : m_work(m_io), m_threadnum(0)
{

}


bool WorkRunner::start(size_t num)
{
    if(num <= 0) return false;

    if(m_theadgroup.size() > 0)
        return false;

    m_threadnum = num;

    for(int i = 0; i < num; i++)
    {
        printf("线程workrunner开启 |[%d] \n", i+1);
        m_theadgroup.create_thread(boost::bind(&ioserver_tp::run, &m_io));
    }

    return true;
}

void WorkRunner::post(std::function<void()> func)
{
    m_io.post(func);
}
