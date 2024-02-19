//
// Created by wenheng on 23年11月18日.
//

#include "WorkThread.h"

WorkThread::WorkThread() :m_id(boost::uuids::random_generator()())
{

}

void WorkThread::start()
{
    m_thread = std::thread(std::bind(&WorkThread::eventloop, this));
}

void WorkThread::eventloop()
{
    while(true)
    {
        std::deque<TaskPtr> queue;

        {
            auto lam = [&](){
                return !m_TaskQueue.empty();
            };

            std::unique_lock<std::mutex> uniqueLock;
            m_cond.wait(uniqueLock, lam);

            m_TaskQueue.swap(queue);
        }

        //TO_DO
        for(auto& task : queue)
        {
            (*task)();
        }


        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

}

WorkThread::~WorkThread()
{
    m_thread.join();
}

bool WorkThread::isSessionTaskExist(const boost::uuids::uuid& sessionid)
{
    std::deque<TaskPtr> queue;
    {
        std::unique_lock<std::mutex> uniqueLock(m_mutex);
        std::back_insert_iterator<std::deque<TaskPtr>> iter(queue);
        std::copy(m_TaskQueue.begin(), m_TaskQueue.end(), iter);
    }

    auto iter = std::find_if(queue.begin(), queue.end(), [sessionid](TaskPtr task)
    {
        return task->m_ownerid == sessionid;
    });

    return iter != queue.end();
}

void WorkThread::push(TaskPtr task)
{
    std::unique_lock<std::mutex> uniqueLock(m_mutex);

    m_TaskQueue.push_back(task);

    m_cond.notify_one();
}

size_t WorkThread::taskCnt()
{
    std::deque<TaskPtr> queue;
    {
        std::unique_lock<std::mutex> uniqueLock(m_mutex);
        std::back_insert_iterator<std::deque<TaskPtr>> iter(queue);
        std::copy(m_TaskQueue.begin(), m_TaskQueue.end(), iter);
    }

    return queue.size();
}


u_char ThreadPool::checkThreadIdxCanWork(boost::uuids::uuid sessionid)
{

    u_char idx = 0;
    for(int i = 0; i < m_workThreads.size(); i++)
    {
        if(m_workThreads[i].isSessionTaskExist(sessionid))
            return i;
    }

    for(int i = 0; i < m_workThreads.size() - 1; i++)
    {
        size_t cnt1 = m_workThreads[i].taskCnt();
        size_t cnt2 = m_workThreads[i+1].taskCnt();

        idx = cnt1 > cnt2 ? (i+1) : i;
    }

    return idx;
}

void ThreadPool::push(TaskPtr task)
{
    u_char idx = checkThreadIdxCanWork(task->m_ownerid);

    {
        std::unique_lock<std::mutex> uniqueLock(m_mutex);
        m_sessionHash[task->m_ownerid] = idx;
    }

    m_workThreads[idx].push(task);
}

ThreadPool::ThreadPool() : m_workThreads(3)
{
    for(int i = 0; i < m_workThreads.size(); i++)
    {
        m_workThreads[i].start();
    }

}
