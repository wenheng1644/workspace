//
// Created by wenheng on 22-10-19.
//

#ifndef ADPTER_ADPTER_H
#define ADPTER_ADPTER_H

#include "iostream"

class Adpter {
public:
    Adpter() = default;
    ~Adpter() = default;

    virtual void Attack();
    virtual void Defend();
};
class other;

class transltor : public Adpter
{
public:
    transltor(other * oth);
    ~transltor() = default;

    void Attack() override;
    void Defend() override;

private:
    other* m_other;
};

class other
{
public:
    other() = default;
    ~other() = default;

    void gongji();
    void fangyu();
};

#endif //ADPTER_ADPTER_H
