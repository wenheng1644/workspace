//
// Created by wenheng on 22-10-25.
//

#ifndef MYTIMER_MYTIMER_H
#define MYTIMER_MYTIMER_H

#include "ctime"
#include "chrono"
#include "iostream"
#include "functional"

#include "boost/format.hpp"

class myTimer {
public:
    myTimer(std::function<void()> f) : m_f(f) {}
    ~myTimer() = default;

    void start(std::chrono::system_clock::duration d);
    void reset(std::function<void()> f);
private:
    std::function<void()> m_f;
};


#endif //MYTIMER_MYTIMER_H
