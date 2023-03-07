//
// Created by wenheng on 22-10-17.
//

#include "comp1.h"
#include "comp2.h"
#include "subject.h"

int main()
{
    boss b;

    comp1 obj1;
    comp2 obj2;

    b.add(std::bind(&comp1::closeWindow, &obj1));
    b.add(std::bind(&comp2::stopPlay, &obj2));

    b.noifty();
    return 0;
}
