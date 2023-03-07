//
// Created by wenheng on 22-10-19.
//

#include "gameRole.h"

gameRole::gameRole() : m_y(0),m_x(0){

}

memnto gameRole::createMemnto() {
    return memnto(m_x, m_y);
}

void gameRole::reBack(const memnto &m) {
    m_x = m.m_x;
    m_y = m.m_y;
}
