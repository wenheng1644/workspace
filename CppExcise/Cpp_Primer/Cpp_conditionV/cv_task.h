//
// Created by нд╨Ц on 2022/5/13.
//

#ifndef CPP_CONDITIONV_CV_TASK_H
#define CPP_CONDITIONV_CV_TASK_H

#define MAX_QUEUE 100

#include "thread"
#include "mutex"
#include "condition_variable"
#include "atomic"
#include "queue"
#include "iostream"

class cv_task {
public:
    cv_task() : m_readFlag(false) {}
    ~cv_task() = default;

    void provider(int id);
    void consumer(int id);

    void atomic_pro();
    void atomic_con();
private:
    std::mutex m_mutex;
    std::condition_variable m_productCv;
    std::condition_variable m_consumeCv;
    std::queue<int> m_queue;

    std::atomic<bool> m_readFlag;
};


#endif //CPP_CONDITIONV_CV_TASK_H
