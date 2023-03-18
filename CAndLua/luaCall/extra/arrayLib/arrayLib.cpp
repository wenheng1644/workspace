//
// Created by wenheng on 23-3-14.
//

#include "arrayLib.h"


static unsigned int* getparam(lua_State* L, unsigned int* mask)
{
    BitArray* a = checkarray(L);
    int index = (int)lua_tointeger(L, 2) - 1;

    luaL_argcheck(L, index >= 0 && index <= a->size, 2, "index out of range");

    *mask = I_BIT(index);
    return &a->values[I_WORD(index)];
}

extern "C"{
    int newarray(lua_State* L)
    {
        int i;
        size_t nbytes;
        BitArray *a;

        int n = (int) luaL_checkinteger(L, 1);
        luaL_argcheck(L, n >= 1, 1, "invalid size");
        nbytes = sizeof(BitArray) + I_WORD(n - 1) * sizeof(unsigned int);
        std::cout << boost::format("CHAR_BIT = %d, BITS_PRE_WORD = %d") % CHAR_BIT % BITS_PRE_WORD << std::endl;
        std::cout << boost::format("nbytes = %d, sizeof(BitArray) = %d, I_WORD(n - 1) = %d") % nbytes % sizeof(BitArray) % I_WORD(n - 1) << std::endl;

        a = (BitArray*) lua_newuserdata(L, nbytes);
        a->size = n;

        for(i = 0; i <= I_WORD(n - 1); i++)
        {
            a->values[i] = 0;
        }

        luaL_getmetatable(L, "arraylib");
        lua_setmetatable(L, -2);
        return 1;
    }

    int setarray(lua_State* L)
    {
        BitArray *a = checkarray(L);
        unsigned int mask;
        unsigned int * value;
        
        luaL_checkany(L, 3);
        value = getparam(L, &mask);

        if(lua_toboolean(L, 3))
        {
            *value |= mask;
        }
        else
        {
            *value &= ~mask;
        }
                

        return 0;
    }

    int getarray(lua_State* L)
    {
        BitArray* a = checkarray(L);
        unsigned int mask;
        unsigned int *value;
        value = getparam(L, &mask);

        lua_pushboolean(L, *value & mask);

        return 1;
    }

    int getsize(lua_State* L)
    {
        BitArray *a = checkarray(L);

        lua_pushinteger(L, a->size);

        return 1;
    }

    int array2string(lua_State* L)
    {
        BitArray *a = checkarray(L);
        lua_pushfstring(L, "array(%d)", a->size);
        return 1;
    }

    int bandarray(lua_State* L)
    {
        BitArray *a = (BitArray*) luaL_checkudata(L, 1, "arraylib");
        BitArray *b = (BitArray*) luaL_checkudata(L, 2, "arraylib");

        luaL_argcheck(L, a != nullptr, 1,"expect array");
        luaL_argcheck(L, b != nullptr && b->size == a->size, 2,"expect array and size same");


        int nbytes = sizeof(BitArray) + I_WORD(a->size - 1) * sizeof(unsigned int);
        BitArray *res = (BitArray*) lua_newuserdata(L, nbytes);

        for(int i = 0; i <= I_WORD(a->size - 1); i++)
        {
            res->values[i] = a->values[i] & b->values[i];
        }
        res->size = a->size;

        luaL_getmetatable(L, "arraylib");
        lua_setmetatable(L, -2);
        return 1;
    }

    int borarray(lua_State* L)
    {
        BitArray *a = (BitArray*) luaL_checkudata(L, 1, "arraylib");
        BitArray *b = (BitArray*) luaL_checkudata(L, 2, "arraylib");

        luaL_argcheck(L, a != nullptr, 1,"expect array");
        luaL_argcheck(L, b != nullptr && b->size == a->size, 2,"expect array and size same");


        int nbytes = sizeof(BitArray) + I_WORD(a->size - 1) * sizeof(unsigned int);
        BitArray *res = (BitArray*) lua_newuserdata(L, nbytes);

        for(int i = 0; i <= I_WORD(a->size - 1); i++)
        {
            res->values[i] = a->values[i] | b->values[i];
        }
        res->size = a->size;

        luaL_getmetatable(L, "arraylib");
        lua_setmetatable(L, -2);

        return 1;
    }

    luaL_Reg arraylib_m[] ={
            {"__index",     getarray},
            {"__newindex",  setarray},
            {"__len",       getsize},
            {"__tostring",  array2string},
            {"__band",      bandarray},
            {"__bor",       borarray},
            {nullptr,       nullptr},
    };

    luaL_Reg arraylib[] = {
            {"new", newarray},
//            {"set", setarray},
//            {"get", getarray},
//            {"size", getsize},
            {nullptr, nullptr},
    };

    int luaopen_arraylib(lua_State* L)
    {
        luaL_newmetatable(L, "arraylib");
        luaL_setfuncs(L, arraylib_m, 0);
        luaL_newlib(L, arraylib);
        return 1;
    }
}