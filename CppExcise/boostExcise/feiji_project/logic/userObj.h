//
// Created by wenheng on 23-6-24.
//

#ifndef FEIJI_PROJECT_USEROBJ_H
#define FEIJI_PROJECT_USEROBJ_H

#define USERBYTES 32


#include "iostream"
#include "boost/asio.hpp"



using namespace boost::asio;

class baseUser{
public:
    baseUser() = default;
    baseUser(const std::string& name);

    virtual ~baseUser() = default;

    const std::string getname() const;
protected:
    char m_name[USERBYTES];
};

class userObj : public baseUser{
public:
    userObj() = default;
    userObj(const std::string& name) : baseUser(name) {}

    void setname(const std::string& name);

    virtual ~userObj() = default;
};


#endif //FEIJI_PROJECT_USEROBJ_H
