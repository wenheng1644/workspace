//
// Created by wenheng on 22-10-17.
//

#include "templateMode.h"
#include "iostream"
int main()
{
    templateMode * wei = new weizhen();
    templateMode * oth = new other();

    std::cout << "wei = " << std::endl;
    wei->dailyPrint();
    std::cout << "oth = " << std::endl;
    oth->dailyPrint();

    return 0;
}