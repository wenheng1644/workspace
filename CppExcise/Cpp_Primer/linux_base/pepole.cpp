//
// Created by wenheng on 22-9-6.
//

#include "pepole.h"

void pepole::showInfo()
{
    std::cout << "hello" << std::endl;
}

void student::showInfo()
{
    std::cout << "name = " << m_name << std::endl;
    std::cout << "sex = " << m_sex << std::endl;
    std::cout << "age = " << m_age << std::endl;
    std::cout << "num = " << m_num << std::endl;
}