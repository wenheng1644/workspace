//
// Created by wenheng on 23-6-25.
//

#ifndef FEIJI_PROJECT_USERENG_H
#define FEIJI_PROJECT_USERENG_H

#include "iostream"
#include "map"
#include "mutex"

#include "../net/netSession.h"
#include "../net/netserver.h"
#include "../net/cmd.h"

template <typename T>
class mySington
{
public:
    static T* getsinton()
    {
        if(!m_obj)
            new mySington<T>;
        return m_obj;
    }

private:
    static T* m_obj;
    mySington<T>() = default;
};


class UserEng : public mySington<UserEng>{
public:
    std::mutex m_cmdMutex;

};


#endif //FEIJI_PROJECT_USERENG_H
