//
// Created by wenheng on 23-3-11.
//

#include "uptransLib.h"

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

void printTable(lua_State* L, int idx)
{
    int type = lua_type(L, idx);
    std::cout << "current type = " << type << std::endl;
    if(type != LUA_TTABLE)
    {
        std::cerr << "it's not a table" << std::endl;
        exit(-1);
    }

    lua_pushnil(L);
    int cnt = 1;
    while(lua_next(L, idx - 1))
    {
        std::cout << boost::format("cnt: %d, data: ") % cnt++ << std::endl;
        stackDump(L);
        lua_pop(L , 1);
    }
    std::cout << "lua_next is done" << std::endl;
    stackDump(L);
}

extern "C"{
    //此处有问题(上值表无法保存)
    int upSettrans(lua_State* L)
    {
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, lua_upvalueindex(1), LUA_TTABLE);
        lua_setfield(L, lua_upvalueindex(1), "table");
        return 1;
    }

    int upGettrans(lua_State* L)
    {
        lua_getfield(L, lua_upvalueindex(1), "table");
        luaL_checktype(L, -1, LUA_TTABLE);
        return 1;
    }

    int upTransliterate(lua_State* L)
    {
        const char* c_str = luaL_checkstring(L, -1);
        if(!c_str)
        {
            std::cerr << "str is nullptr...." << std::endl;
            return 0;
        }
        lua_getfield(L, lua_upvalueindex(1), "table");
        luaL_checktype(L, -1, LUA_TTABLE);

        std::string stdstr(c_str);
        std::string res(stdstr);

        for(const auto& c : stdstr)
        {
            auto lam = [c](char x)
            {
                if(x == c) return true;
                return false;
            };

            lua_getfield(L, -1, std::string(1, c).c_str());

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

    const luaL_Reg uptransLib[] = {
            {"upSettrans", upSettrans},
            {"upGettrans", upGettrans},
            {"upTransliterate", upTransliterate},
            {nullptr, nullptr},
    };

    int luaopen_uptranslib(lua_State* L)
    {
        luaL_newlibtable(L, uptransLib);
        lua_newtable(L);
        luaL_setfuncs(L, uptransLib, 1);
        return 1;
    }
}
