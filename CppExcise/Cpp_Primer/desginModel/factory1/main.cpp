//
// Created by wenheng on 22-10-14.
//
#include "factoryOp.h"
#include <iostream>
int main()
{
    factoryOp f;

    char c;

    while(std::cin >> c)
    {
        if(c != '+' && c != '*' && c != '/')
            continue;

        AbstractOp* op = f.createOp(c);

        if(!op)
            break;
        printf("your data = ");
        op->getNumber();
        std::cout << "ans = " << op->result() << std::endl;

        delete op;

    }


    return 0;
}
