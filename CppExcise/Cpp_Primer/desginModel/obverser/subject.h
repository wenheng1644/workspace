//
// Created by wenheng on 22-10-17.
//

#ifndef OBVERSER_SUBJECT2_H
#define OBVERSER_SUBJECT2_H

#include <functional>
#include <iostream>
#include <unordered_set>
#include "set"
#include "list"
class subject {
public:
    subject() = default;
    virtual ~subject() = default;
    virtual void noifty() = 0;

protected:
    std::list<std::function<void()>> m_objs;
};

class boss : public subject
{
public:
    boss() = default;
    ~boss() = default;

    void add(std::function<void()> func);
    void noifty() override;
};

#endif