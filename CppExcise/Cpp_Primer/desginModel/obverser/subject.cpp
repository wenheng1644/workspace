//
// Created by wenheng on 22-10-17.
//

#include "subject.h"

void boss::noifty() {
    for(auto func : m_objs)
    {
        func();
    }
    std::cout << "noifty done" << std::endl;
}

void boss::add(std::function<void()> func) {
    m_objs.insert(m_objs.end(), func);
}
