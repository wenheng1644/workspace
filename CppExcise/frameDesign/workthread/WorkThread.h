//
// Created by wenheng on 23年11月18日.
//

#ifndef WORKTHREAD_WORKTHREAD_H
#define WORKTHREAD_WORKTHREAD_H

#include "thread"
#include "functional"

#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_serialize.hpp"
#include "boost/uuid/uuid_hash.hpp"

#include "mutex"
#include "shared_mutex"
#include "condition_variable"

#include "queue"
#include "map"
#include "unordered_map"

#include "iterator"

#include "threadSafe_Container.h"
#include "task.h"

class WorkThread {
public:
    WorkThread();

    bool isSessionTaskExist(const boost::uuids::uuid& sessionid);
    void start();
    size_t taskCnt();
    void push(TaskPtr task);

    ~WorkThread();

private:
    boost::uuids::uuid m_id;
    std::thread m_thread;

    std::mutex m_mutex;
    std::condition_variable m_cond;

    std::deque<TaskPtr> m_TaskQueue;
    void eventloop();
};


class ThreadPool
{
public:
    ThreadPool();

    void push(TaskPtr task);

private:
    std::deque<WorkThread> m_workThreads;
    std::mutex m_mutex;

    std::unordered_map<boost::uuids::uuid, u_char> m_sessionHash;


    u_char checkThreadIdxCanWork(boost::uuids::uuid sessionid);
};


#endif //WORKTHREAD_WORKTHREAD_H
