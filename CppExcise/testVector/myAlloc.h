//
// Created by wenheng on 22-10-30.
//

#ifndef TESTVECTOR_MYALLOC_H
#define TESTVECTOR_MYALLOC_H
#include <iostream>
#include <memory>

template<typename T>
class myAlloc {
//    typedef unsigned int uint;
public:
    myAlloc();
    ~myAlloc();

    void allocMem(::uint cnt);
    void construct();
};


#endif //TESTVECTOR_MYALLOC_H
