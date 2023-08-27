//
// Created by wenheng on 23年8月26日.
//

#include "threadPool.h"

#include "algorithm"


threadFunc threadPool::workFunc = workThread;
threadFunc threadPool::managerFunc = managerThread;

void workThread(threadPool& pool)
{
    {
        std::lock_guard<std::recursive_mutex> gl(pool.m_dataMutex);
        std::cout << boost::format("工作线程[id = %d] 启动加入, 已有线程数： %d") % std::this_thread::get_id() \
                    % pool.m_workThreads.size() << std::endl;
    }

    while(true)
    {
//        netMsgTaskQueue<int>& tasks = pool.m_tasks;

        while(true)
        {

            {
                std::lock_guard<std::recursive_mutex> gl(pool.m_dataMutex);
                if(pool.m_tasks.getTaskSize() > 0) break;
            }

//            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            {
                std::lock_guard<std::recursive_mutex> gl(pool.m_dataMutex);
                if(pool.m_busyCnt > 0) pool.m_busyCnt--;
            }

            std::unique_lock<std::mutex> ul(pool.m_emptyMutex);
            pool.m_emptyCond.wait(ul, [&](){
                return pool.m_tasks.getTaskSize() > 0;
            });
            std::cout << boost::format("工作线程[id = %d] 收到通知， 处理任务") % std::this_thread::get_id() << std::endl;
            break;
        }

        std::lock_guard<std::recursive_mutex> gl(pool.m_dataMutex);
        if(pool.m_tasks.getTaskSize() > 0)
        {
            pool.m_busyCnt++;
            int& data = pool.m_tasks.takeTask();
            std::cout << boost::format("线程[id = %d] 处理任务 = %d") % std::this_thread::get_id() % data << std::endl;
        }

    }
}

void managerThread(threadPool& pool)
{

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        auto& tasks = pool.m_tasks;

        {
            std::lock_guard<std::recursive_mutex> rl(pool.m_dataMutex);
            if(tasks.getTaskSize() > 0)
            {
                std::lock_guard<std::mutex> gl(pool.m_emptyMutex);
                std::cout << boost::format("监控线程[id = %d] 通知工作线程处理任务") % std::this_thread::get_id() << std::endl;
                pool.m_emptyCond.notify_all();
            }

            std::cout << boost::format("当前忙线程数量 = %d") % pool.m_busyCnt << std::endl;
        }
    }
}

void threadPool::threadExit()
{
    auto threadid = std::this_thread::get_id();

    std::lock_guard<std::mutex> gl(m_workMutex);
//    for(auto& thread : m_workThreads)
//    {
//        if(thread.get_id() == threadid)
//        {
//            pthread_cancel(thread.native_handle());
//        }
//    }

    auto iter = std::find_if(m_workThreads.begin(), m_workThreads.end(), [threadid](std::thread& t){
        return t.get_id() == threadid;
    });

    if(iter != m_workThreads.end()) {
        std::thread &delThread = *iter;
        pthread_cancel(delThread.native_handle());

        std::cout << boost::format("线程[id = %d] 退出1, 销毁线程前线程数量 = %d") % threadid % m_workThreads.size()
                  << std::endl;
        m_workThreads.erase(iter, m_workThreads.end());
        std::cout << boost::format("线程[id = %d] 退出2, 销毁线程后线程数量 = %d") % threadid % m_workThreads.size()
                  << std::endl;
    }
    else
    {
        std::cerr << boost::format("线程[id = %d] 退出失败, 工作线程池找不到") % threadid << std::endl;
        for(auto& thread : m_workThreads)
        {
            std::cerr << boost::format("线程[id = %d] 遍历当前线程池的id") % thread.get_id() << std::endl;
        }

    }




}

void createThread(threadPool& pool)
{
    while(true)
    {

        {
            std::lock_guard<std::recursive_mutex> gl(pool.m_dataMutex);
            auto& tasks = pool.m_tasks;

            int data = std::abs(rand()) % 1000;
            tasks.addTask(data);
            std::cout << boost::format("生产者线程[id = %d] 生产 data = %d") % std::this_thread::get_id() % data << std::endl;

        }



        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }

}

threadPool::threadPool(size_t minThreadCnt) : m_aliveCnt(0), m_busyCnt(0), m_exitCnt(0)
{

}

void threadPool::run()
{
    m_managerThread = std::thread(&managerThread, std::ref(*this));

    for(int i = 0; i < MAX_THREADCOUNT; i++)
    {
        m_workThreads.push_back(std::thread(&workThread, std::ref(*this)));

        {
            std::lock_guard<std::recursive_mutex> gl(m_dataMutex);
            m_aliveCnt++;
//            m_busyCnt++;
        }
    }


}

threadPool::~threadPool()
{
    m_managerThread.join();
    for(auto& t : m_workThreads)
        t.join();
}
