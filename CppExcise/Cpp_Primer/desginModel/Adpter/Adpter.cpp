//
// Created by wenheng on 22-10-19.
//

#include "Adpter.h"

void Adpter::Attack() {
    std::cout << "attack!" << std::endl;
}

void Adpter::Defend() {
    std::cout << "defend!" << std::endl;
}

void other::gongji() {
    std::cout << "攻击" << std::endl;
}

void other::fangyu() {
    std::cout << "防御" << std::endl;
}

void transltor::Attack() {
    m_other->gongji();
}

void transltor::Defend() {
    m_other->fangyu();
}

transltor::transltor(other *oth) : Adpter(), m_other(oth){

}
