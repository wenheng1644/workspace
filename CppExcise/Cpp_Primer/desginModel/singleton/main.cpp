//
// Created by wenheng on 22-10-18.
//

#include "singleton.h"
#include "iostream"
#include <thread>


int main()
{
    singleton* p1 = singleton::getInstance();
    singleton* p2 = singleton::getInstance();

    if(p1 == p2)
        std::cout << "yes" << std::endl;
    else
        std::cout << "no" << std::endl;
}