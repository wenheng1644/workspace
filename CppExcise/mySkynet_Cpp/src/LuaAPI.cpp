#include "LuaAPI.h"

#include "stdint.h"
#include "unistd.h"
#include "cstring"
#include "string"
#include "Sunnet.h"

void LuaAPI::Register(lua_State *luaState)
{
    static luaL_Reg lualib[] = {
        {"NewService", NewService},
        {"KillService", KillService},
        {nullptr, nullptr},
    };

    luaL_newlib(luaState, lualib);
    lua_setglobal(luaState, "sunnet");
}

int LuaAPI::NewService(lua_State *luaState)
{
    int num = lua_gettop(luaState);
    
    if(lua_isstring(luaState, 1) == 0)
    {
        lua_pushinteger(luaState, -1);
        return 1;
    }

    size_t len = 0;
    const char* c_str = lua_tolstring(luaState, 1, &len);
    char* newStr = new char[len+1];
    newStr[len] = '\0';

    
    memcpy(newStr, c_str, len);

    auto t = std::make_shared<std::string>(newStr);

    auto id = Sunnet::inst->NewService(t);

    lua_pushinteger(luaState, id);
    return 1;
}

int LuaAPI::KillService(lua_State *luaState)
{
    
    int num = lua_gettop(luaState);
    if(num != 1)
    {
        lua_pushboolean(luaState, false);
        lua_pushstring(luaState, "num count is not 1");
        return 2;
    }

    if(lua_isinteger(luaState, 1) == 0)
    {
        lua_pushboolean(luaState, false);
        lua_pushstring(luaState, "arg type is not number");
        return 2;
    }

    size_t id = lua_tointeger(luaState, 1);
    Sunnet::inst->KillService(id);

    lua_pushboolean(luaState, true);
    lua_pushstring(luaState, "success");

    return 2;
}
