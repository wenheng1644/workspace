//
// Created by нд╨Ц on 2022/4/23.
//

#ifndef THREAD_EXCISE_TASK_H
#define THREAD_EXCISE_TASK_H

#include "thread"
#include "mutex"
#include "condition_variable"

#include "queue"
#include "iostream"

class task {
public:
    task() = default;
    ~task() = default;

    void proudct_task();
    void consume_task();

private:
    std::mutex m_mutex;
    std::deque<int> m_tasks;
    std::condition_variable m_cv;
};


#endif //THREAD_EXCISE_TASK_H
