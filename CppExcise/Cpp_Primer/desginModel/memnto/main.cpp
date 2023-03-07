//
// Created by wenheng on 22-10-19.
//

#include <gameRole.h>
#include <memnto.h>

int main()
{
    gameRole r;
    careMaker c(r.createMemnto());

    r.reBack(c.Memnto());

    return 0;

}
