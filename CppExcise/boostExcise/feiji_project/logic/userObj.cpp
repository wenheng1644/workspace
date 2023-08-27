//
// Created by wenheng on 23-6-24.
//

#include "boost/format.hpp"

#include "userObj.h"

baseUser::baseUser(const std::string& name)
{
    memcpy(m_name, name.c_str(), sizeof(m_name));
}

const std::string baseUser::getname() const {
    return std::string(m_name);
}


void userObj::setname(const std::string &name) {

    if(name.empty())
    {
        std::cerr << boost::format("name is empty") << std::endl;
        return;
    }

    size_t bytes = strlen(name.c_str());
    if(bytes > USERBYTES)
    {
        std::cerr << boost::format("name bytes is to long | %d") % bytes << std::endl;
        return;
    }

    memcpy(m_name, name.c_str(), bytes);
}
