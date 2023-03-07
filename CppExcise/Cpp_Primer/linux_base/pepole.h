//
// Created by wenheng on 22-9-6.
//

#ifndef LINUX_BASE_PEPOLE_H
#define LINUX_BASE_PEPOLE_H

#include "string"
#include "iostream"

class pepole {
public:
    explicit pepole(const std::string& name, const std::string & sex,ushort age) : m_name(name), m_sex(sex), m_age(age) {}

    virtual void showInfo() = 0;
    virtual ~pepole() {}

protected:
    std::string m_name;
    std::string m_sex;
    ushort m_age;
};


class student : public  pepole
{
public:
    explicit student(const std::string& name, const std::string & sex,ushort age, const std::string& num) \
    : pepole(name, sex, age), m_num(num) {}

    virtual void showInfo() override;

    virtual ~student(){}

private:
    std::string m_num;
};


#endif //LINUX_BASE_PEPOLE_H
