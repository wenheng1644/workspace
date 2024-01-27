#include "WorkRunner.h"

WorkRunner::WorkRunner() : m_work(m_io)
{
    m_threadnum = 3;

    for(int i = 0; i < m_threadnum; i++)
    {
        // ioserver_tp::work w(m_io);
        printf("WorkRunner |[%d] io管理放入线程\n", i+1);
        m_theadgroup.create_thread(boost::bind(&ioserver_tp::run, &m_io));
    }
}

void WorkRunner::post(std::function<void()> func)
{
    // m_io.post(func);
}
