//
// Created by wenheng on 22-10-20.
//

#include "command.h"
#include <iostream>

void worker::makeTea() {
    std::cout << "make a cup of tea" << std::endl;
}

void worker::makeMeat() {
    std::cout << "make some meat for client~" << std::endl;
}

void TeaCommand::excute() {
    m_worker->makeTea();
}

void MeatCommand::excute() {
    m_worker->makeMeat();
}
