//
// Created by wenheng on 22-10-20.
//

#include "command.h"

int main()
{
    waiter waiter;
    worker worker;
    command* tea = new TeaCommand(&worker);
    command* meat = new MeatCommand(&worker);

    waiter.setCommand(tea);
    waiter.noifty();

    waiter.setCommand(meat);
    waiter.noifty();

    return 0;
}