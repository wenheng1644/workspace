//
// Created by wenheng on 22-10-19.
//

#include "Adpter.h"
#include "iostream"
int main()
{
    other oth;
    Adpter a;
    transltor t(&oth);

    a.Attack();



    a.Defend();

    t.Attack();
    t.Defend();

    return 0;
}

