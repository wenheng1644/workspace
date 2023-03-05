//
// Created by 文恒 on 2022/5/13.
//

#include "cv_task.h"

void cv_task::provider(int id)
{
    while(true)
    {
        {
            std::unique_lock<std::mutex> ul(m_mutex);
//            m_consumeCv.wait(ul, [this](){ return m_queue.size() < MAX_QUEUE;}); //未满则继续生产

            for(int i = 0; i < 5; i++)
            {
                m_queue.push(i);
            }

            std::cout << "provider Id: " << id  << "\tthread Id: " << std::this_thread::get_id() << std::endl;
        }

        m_productCv.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void cv_task::consumer(int id)
{
    while(true)
    {
        {
            std::unique_lock<std::mutex> ul(m_mutex);
            m_productCv.wait(ul, [this](){ return !m_queue.empty(); });

            int val = m_queue.front();
            m_queue.pop();

            std::cout << "get val: " << val << "\tthread id: " << std::this_thread::get_id() << std::endl;
        }

//        m_consumeCv.notify_all();
    }

}

void cv_task::atomic_pro()
{
    while(true)
    {
        if(!m_readFlag.load())
        {
            std::cout << "false and set true" << std::endl;
            m_readFlag.store(true);

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

}

void cv_task::atomic_con()
{
    while(true)
    {
        if(m_readFlag.load())
        {
            std::cout << "deal with the flag" << std::endl;
            m_readFlag.store(false) ;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

}
