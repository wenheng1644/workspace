//
// Created by wenheng on 23-5-1.
//

#ifndef BOOST_ASIO_NEW_LOGMANAGER_H
#define BOOST_ASIO_NEW_LOGMANAGER_H

#include "iostream"
#include "string"
#include "deque"

#include "boost/format.hpp"

#include "../CScriptSystem/CScriptSystem.h"
#include "../netMsg/netMsg.h"
#include "../common/commonClass.h"

class logManager {
public:
    static logManager* getLogManager()
    {
        if(!m_manager)
            m_manager = new logManager;
        return m_manager;
    }

    bool writeDataToFile(const netMsgList& netMsgs);

private:
    logManager() = default;

    static logManager* m_manager;
};


#endif //BOOST_ASIO_NEW_LOGMANAGER_H
