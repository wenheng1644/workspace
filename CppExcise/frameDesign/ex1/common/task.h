//
// Created by wenheng on 23年9月23日.
//

#ifndef EX1_TASK_H
#define EX1_TASK_H

#include "string"
#include "iostream"

#include "../netResolver/base_cmd.h"

#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"


enum TaskFromType
{
    TASK_CLIENT, //客户端发送
    TASK_SERVER, //服务器内部
};

enum TaskMsgType {
    TASK_PERSONAL,        //个人消息
    TASK_BROADCAST,       //广播消息
};

class Task {
public:
    Task() : m_from(TASK_CLIENT), m_taskType(TASK_PERSONAL) {}
    Task(boost::uuids::uuid uuid, netMsgPtr data) :m_ownerid(uuid), m_taskid(boost::uuids::random_generator()()), \
        m_msg(data), m_from(TASK_CLIENT), m_taskType(TASK_PERSONAL) {}
    Task(boost::uuids::uuid uuid, netMsg data);

    template<class T>
    static std::shared_ptr<Task> makeTask(T& cmd);
//    Task& operator=(const Task& other)
//    {
//
//    }
//

    bool operator==(const Task& other)
    {
        return m_taskid == other.m_taskid;
    }

    boost::uuids::uuid m_ownerid;
    boost::uuids::uuid m_taskid;
    netMsgPtr m_msg;
    TaskFromType m_from;
    TaskMsgType m_taskType;
};

typedef std::shared_ptr<Task> TaskPtr;

template<class T>
TaskPtr Task::makeTask(T& cmd) {
    auto net = netQtResolver::getNetDataByCmd(cmd);
    netMsg msg(cmd.type, cmd.subtype, net);

    TaskPtr task(new Task(boost::uuids::random_generator()(), msg));
    return task;
}

#endif //EX1_TASK_H
