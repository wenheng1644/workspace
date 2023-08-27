//
// Created by wenheng on 23年8月26日.
//

#ifndef CMD_PROJECT_THREADPOOL_H
#define CMD_PROJECT_THREADPOOL_H

#include "iostream"
#include "string"
#include "deque"

#include "thread"
#include "condition_variable"
#include "mutex"

#include "netMsgTask.h"

#include "boost/format.hpp"

#define MAX_THREADCOUNT     3
#define MIN_THREADCOUNT     1



class threadPool;
typedef void (*threadFunc)(threadPool&);

void workThread(threadPool& pool);
void managerThread(threadPool& pool);
void createThread(threadPool& pool);


class threadPool {
    friend void workThread(threadPool& pool);
    friend void managerThread(threadPool& pool);
    friend void createThread(threadPool& pool);
public:
    explicit threadPool(size_t minThreadCnt = 1);
    ~threadPool();
    void run();
    void threadExit();

private:
    std::deque<std::thread> m_workThreads;
    std::thread m_managerThread;

    std::mutex m_workMutex;
    std::mutex m_managerMutex;

    std::mutex m_emptyMutex;
    std::condition_variable m_emptyCond;

    std::recursive_mutex m_dataMutex;
    size_t m_aliveCnt;
    size_t m_busyCnt;
    size_t m_exitCnt;

    netMsgTaskQueue<int> m_tasks;

    static threadFunc workFunc;
    static threadFunc managerFunc;
};


#endif //CMD_PROJECT_THREADPOOL_H
