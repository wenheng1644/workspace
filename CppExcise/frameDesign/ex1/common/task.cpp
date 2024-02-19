//
// Created by wenheng on 23年9月23日.
//

#include "task.h"

Task::Task(boost::uuids::uuid uuid, netMsg data) : m_ownerid(uuid), m_taskid(boost::uuids::random_generator()()), \
    m_from(TASK_CLIENT), m_taskType(TASK_PERSONAL)
{
    m_msg = netMsgPtr(new netMsg(data));
}


