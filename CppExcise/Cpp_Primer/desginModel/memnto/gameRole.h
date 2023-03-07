//
// Created by wenheng on 22-10-19.
//

#ifndef MEMNTO_GAMEROLE_H
#define MEMNTO_GAMEROLE_H

#include "memnto.h"

class gameRole {
public:
    gameRole();
    ~gameRole() = default;

    memnto createMemnto();
    void reBack(const memnto& m);

private:
    int m_x;
    int m_y;
};


#endif //MEMNTO_GAMEROLE_H
