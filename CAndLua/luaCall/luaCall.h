//
// Created by нд╨Ц on 2023/2/13.
//

#ifndef LUACALL_LUACALL_H
#define LUACALL_LUACALL_H

#include "iostream"
#include "stdio.h"
#include "stdarg.h"
#include "string"

extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#define LUAPATH "..//config//luaMain.lua"

class luaCall {
public:
    static luaCall* generator()
    {
        if(!m_luaCallobj)
            m_luaCallobj = new luaCall;
        return m_luaCallobj;
    }

    void vCall(const char* funcname, ...);
    std::string getLuaVarByKey(const char* key);
private:
    luaCall();
    static luaCall* m_luaCallobj;
    lua_State* m_luaState;
};

static void printError(lua_State* L, const char* fmt, ...)
{
    va_list l;
    va_start(l, fmt);
    vfprintf(stderr,fmt, l);
    va_end(l);

    lua_close(L);
    exit(-1);
}


#endif //LUACALL_LUACALL_H
