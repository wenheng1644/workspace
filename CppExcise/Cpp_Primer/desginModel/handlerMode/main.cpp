//
// Created by wenheng on 22-10-18.
//

#include "handler.h"

int main()
{
    banZhang b;
    laoShi l;
    xiaoZhang x;

    b.setPreHandler(&l);
    l.setPreHandler(&x);


    b.handleRequest(5);

    return 0;
}