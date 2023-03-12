#include "transLib.h"

#include <iostream>
#include "string"
#include "algorithm"
#include "boost/format.hpp"

void stackDump(lua_State * L)
{
    int i;
    int top = lua_gettop(L);

    for(i = 1; i <= top; ++i)
    {
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING:
                std::cout << boost::format("(string)i = %d: %s") % i % lua_tostring(L,i) << std::endl;
                break;
            case LUA_TBOOLEAN:
                std::cout << boost::format("(bool)i = %d: %s") %i % (lua_toboolean(L,i) ? "true" : "false") << std::endl;
                break;
            case LUA_TNUMBER:
                std::cout << boost::format("(number)i = %d: %g") % i % lua_tonumber(L,i) << std::endl;
                break;
            case LUA_TTABLE:
                std::cout << boost::format("(table)i = %d") % i << std::endl;
                break;
            case LUA_TFUNCTION:
                std::cout << boost::format("(function)i = %d") %i << std::endl;
                break;
            default:
                std::cout << boost::format("(other)i = %d: %s") % i % lua_type(L,i) << std::endl;
                break;
        }
    }
    printf("\n");
}

extern "C"{
    static int g_ref = -1;
    int cSettrans(lua_State* L)
    {
        luaL_checktype(L, -1, LUA_TTABLE);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);
        g_ref = ref;
        std::cout << "set ok: " << ref << std::endl;

        return 0;
    }

    int cGettrans(lua_State* L)
    {
        if(g_ref == -1)
        {
            std::cerr << "cGettrans | no value!!!" << std::endl;
            return 0;
        }

        lua_rawgeti(L, LUA_REGISTRYINDEX, g_ref);

        return 1;
    }

    int cTransliterate(lua_State* L)
    {
//        cGettrans(L);
        std::cout << "cTransliterate | g_ref = " << g_ref << std::endl;
        if(g_ref == -1)
        {
            std::cerr << "error, no table..." << std::endl;
            exit(-1);
        }
        const char* c_str = luaL_checkstring(L , -1);
        std::cout << "cTransliterate | c_str = " << c_str << std::endl;
        stackDump(L);

        lua_rawgeti(L, LUA_REGISTRYINDEX, g_ref);
        stackDump(L);
//        luaL_checktype(L , -1, LUA_TTABLE);

        std::string stdstr(c_str);
        std::string res(stdstr);

        for(const auto& c : stdstr)
        {
            auto lam = [c](char x) {
                if(x == c) return true;
                return false;
            };
            lua_getfield(L, 2, std::string(1, c).c_str());
            int type = lua_type(L, -1);

            if(type == LUA_TBOOLEAN)
            {
                bool status = lua_toboolean(L, -1);
                if(!status)
                {
                    auto iter = std::remove_if(res.begin(), res.end(), lam);
                    res.erase(iter, res.end());
                }
            }

            if(type == LUA_TSTRING)
            {
                const char* rep_cstr = luaL_checkstring(L, -1);
                std::replace_if(res.begin(), res.end(), lam, *rep_cstr);
            }
            lua_pop(L, 1);
        }
        lua_pushstring(L, res.c_str());
        return 1;
    }

static const struct luaL_Reg libs [] = {
        {"settrans" , cSettrans},
        {"gettrans", cGettrans},
        {"transliterate", cTransliterate},
        {nullptr, nullptr},
    };

    int luaopen_translib(lua_State* L)
    {
        luaL_newlib(L, libs);
        return 1;
    }
}