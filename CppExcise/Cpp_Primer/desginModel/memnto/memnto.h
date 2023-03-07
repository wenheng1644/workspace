//
// Created by wenheng on 22-10-19.
//

#ifndef MEMNTO_MEMNTO_H
#define MEMNTO_MEMNTO_H

class gameRole;

class memnto {
    friend gameRole;
public:
    memnto(int x, int y = 0) : m_x(x), m_y(y) {}
    ~memnto() = default;

private:
    int m_x;
    int m_y;
};


class careMaker
{
public:
    careMaker(const memnto& m) : m_memnto(m) {}
    ~careMaker() = default;

    void setMemnto(const memnto& m);
    memnto Memnto() { return m_memnto;}
private:
    memnto m_memnto;
};

#endif //MEMNTO_MEMNTO_H
