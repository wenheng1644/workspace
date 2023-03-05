//
// Created by нд╨Ц on 2022/4/23.
//

#include "task.h"

void task::proudct_task()
{

    int taskId = 0;
    while(true)
    {
        {
            std::lock_guard<std::mutex> u_lock(m_mutex);
            m_tasks.push_back(taskId);

            std::cout << "product taskId: " << taskId << "\tthread id: " << std::this_thread::get_id() << std::endl;
            taskId++;
        }

        if(!m_tasks.empty())
            m_cv.notify_one();
    }
}

void task::consume_task()
{
    while(true)
    {
        std::unique_lock<std::mutex> lock_guard(m_mutex);
        while(m_tasks.empty())
        {
            m_cv.wait(lock_guard);
        }

        int taskId = m_tasks.front();
        m_tasks.pop_front();

        std::cout << "consume taskId: " << taskId << "\tthreadId: " << std::this_thread::get_id() << std::endl;

    }
}
