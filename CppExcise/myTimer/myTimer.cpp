//
// Created by wenheng on 22-10-25.
//

#include "myTimer.h"
#include "thread"

void myTimer::start(std::chrono::system_clock::duration d) {

    auto lamba = [this](std::chrono::system_clock::duration d) {
        std::this_thread::sleep_for(d);
        std::cout << boost::format("[from lamba] start to do something thread id = %d") % std::this_thread::get_id() << std::endl;
        m_f();
    };
    std::thread t(lamba, d);
    t.detach();
}

void myTimer::reset(std::function<void()> f) {
    m_f = std::move(f);
}
