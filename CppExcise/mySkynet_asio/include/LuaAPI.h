#ifndef LUAAPI
#define LUAAPI

#pragma once
#include "Service.h"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_io.hpp"
extern "C"{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

#include "sol/sol.hpp"

struct   ServerArgs;

class LuaAPI
{
public:
    static void Register(sol::state& lua);

    static int NewService(const std::string& name, sol::variadic_args args);
    static void KillService(int svrid);
    static void Send(int source, int to, sol::variadic_args args);
    static void Listen(int svrid, int port, const std::string& ip);
    static void CloseConn(const std::string socket_uuid_str);
    static int Write(lua_State* luaState);
    static bool RegisterSvr(const std::string& svr_name, int svrid);
    static int GetSvrIdByName(const std::string& svr_name);
    static int GetSvrId();
    static int Uuid2String(lua_State* luaState);
    static int String2Uuid(lua_State* luaState);

private:
    static void LoadSystemConfig(sol::state& lua);
};


#endif
