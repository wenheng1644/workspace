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
        {"Send", Send},
        {"Write", Write},
        {"Listen", Listen},
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
    num = lua_gettop(luaState); 
    std::cout << "the num = " << num << std::endl;
    lua_pushboolean(luaState, true);
    lua_pushstring(luaState, "success");
    Sunnet::inst->KillService(id);

    return 2;
}

int LuaAPI::Send(lua_State *luaState)
{
    // Sunnet::inst->Send()
    int num = lua_gettop(luaState);
     if(num != 3)
    {
        lua_pushboolean(luaState, false);
        return 1;
    }

    if(!lua_isinteger(luaState, 1))
    {
        lua_pushboolean(luaState, false);
        return 1;
    }

    if(!lua_isinteger(luaState, 2))
    {
        lua_pushboolean(luaState, false);
        return 1;
    }

    if(!lua_isstring(luaState, 3))
    {
        lua_pushboolean(luaState, false);
        return 1;
    }

    size_t source = lua_tointeger(luaState, 1);
    size_t to = lua_tointeger(luaState, 2);

    size_t len = 0;
    const char* buff = lua_tolstring(luaState, 3, &len);

    char* newStr = new char[len + 1];
    newStr[len] = '\0';

    memcpy(newStr, buff, len);

    auto msg = std::make_shared<ServiceMsg>();
    msg->m_buff = std::shared_ptr<char>(newStr);
    msg->m_size = len;
    msg->m_source = source;
    msg->m_type = BaseMsg::TYPE::SERVICE;

    Sunnet::inst->Send(to, msg);

    lua_pushboolean(luaState, true);

    return 1;
}

int LuaAPI::Listen(lua_State *luaState)
{
    // Sunnet::inst->Listen()
    int num = lua_gettop(luaState);
    if(num != 2)
    {
        lua_pushboolean(luaState, false);
        return 1;
    }

    if(!lua_isinteger(luaState, 1) || !lua_isinteger(luaState, 1))
    {
        lua_pushboolean(luaState, false);
        return 1;
    }

    size_t port = lua_tointeger(luaState, 1);
    size_t svrid = lua_tointeger(luaState, 2);

    Sunnet::inst->Listen(port, svrid);
    lua_pushboolean(luaState, true);

    return 1;
}

int LuaAPI::CloseConn(lua_State *luaState)
{
    int num = lua_gettop(luaState);
    if(num != 1)
    {
        lua_pushboolean(luaState, false);
        return 1;
    }

    if(lua_isinteger(luaState, 1) == 0)
    {
        lua_pushboolean(luaState, false);
        return 1;
    }

    size_t fd = lua_tointeger(luaState, 1);
    Sunnet::inst->CloseConn(fd);

    lua_pushboolean(luaState, true);
    return 0;
}

int LuaAPI::Write(lua_State *luaState)
{
    // Sunnet::inst->GetConn();
    int num = lua_gettop(luaState);
    if(num != 2)
    {
        lua_pushboolean(luaState, false);
        return 1;
    }

    if(!lua_isinteger(luaState, 1))
    {
        lua_pushboolean(luaState, false);
        return 1;
    }

    if(!lua_isstring(luaState, 2))
    {
        lua_pushboolean(luaState, false);
        return 1;
    }

    size_t fd = lua_isinteger(luaState, 1);

    size_t len = 0;
    const char* buff = lua_tolstring(luaState, 2, &len);
    write(fd, buff, len);

    lua_pushboolean(luaState, true);
    return 1;
}
