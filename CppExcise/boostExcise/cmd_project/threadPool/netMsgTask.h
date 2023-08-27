//
// Created by wenheng on 23年8月26日.
//

#ifndef CMD_PROJECT_NETMSGTASK_H
#define CMD_PROJECT_NETMSGTASK_H

#include "deque"
#include "iostream"

#include "mutex"

template<typename T>
class netMsgTaskQueue {
public:
    netMsgTaskQueue() = default;

    void addTask(const T& task);
    T& takeTask();

    size_t getTaskSize();

//    std::recursive_mutex m_taskMutex;

private:
    std::deque<T> m_tasks;
};


template<typename T>
void netMsgTaskQueue<T>::addTask(const T &task)
{
//    std::lock_guard<std::recursive_mutex> gl(m_taskMutex);
    m_tasks.push_back(task);
}

template<typename  T>
T& netMsgTaskQueue<T>::takeTask()
{
//    std::lock_guard<std::recursive_mutex> gl(m_taskMutex);
    if(m_tasks.empty())
        throw std::exception();

    T& task = m_tasks.front();

    m_tasks.pop_front();

    return task;
}

template<typename T>
size_t netMsgTaskQueue<T>::getTaskSize()
{
//    std::lock_guard<std::recursive_mutex> gl(m_taskMutex);
    return m_tasks.size();
}

#endif //CMD_PROJECT_NETMSGTASK_H
