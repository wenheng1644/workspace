//
// Created by wenheng on 23-3-14.
//

#ifndef LUACALL_ARRAYLIB_H
#define LUACALL_ARRAYLIB_H

#include <iostream>
#include "boost/format.hpp"
#include <limits.h>
//#define CHAR_BIT        8
#define BITS_PRE_WORD   (CHAR_BIT * sizeof(unsigned  int))
#define I_WORD(i)       ((unsigned int)(i) / BITS_PRE_WORD)
#define I_BIT(i)        (1 << ((unsigned int)(i) % BITS_PRE_WORD))

#define I_TEST(i)       ((unsigned int)(i) % BITS_PRE_WORD)

extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

typedef struct BitArray{
    int size;
    unsigned int values[1];
}BitArray;

#define checkarray(L) ((BitArray *)luaL_checkudata(L, 1, "Luabook.array"))

#endif //LUACALL_ARRAYLIB_H
