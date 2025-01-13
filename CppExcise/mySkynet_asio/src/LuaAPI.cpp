#include "LuaAPI.h"

#include "stdint.h"
#include "unistd.h"
#include "cstring"
#include "string"
#include "Sunnet.h"
#include <iostream>

#include "boost/assert.hpp"
#include "boost/thread.hpp"

#include "net/NetData.h"

void LuaAPI::Register(sol::state& lua)
{
    LoadSystemConfig(lua);

    sol::table sunnet = lua.create_named_table("sunnet");
    // sunnet.set_function("NewService", NewService);
    sunnet["NewService"] = sol::as_function(NewService);
    sunnet.set_function("KillService", KillService);
    sunnet.set_function("Send", Send);
    sunnet.set_function("Listen", Listen);
    sunnet.set_function("RegisterSvr", RegisterSvr);
    sunnet.set_function("GetSvrIdByName", GetSvrIdByName);

    lua.create_named_table("CommandFuncs");
    lua.set("ACCEPT", ACCEPT);
    lua.set("DATA", DATA);
    lua.set("CLOSE", CLOSE);
}

int LuaAPI::NewService(const std::string& name, sol::variadic_args args)
{

    auto t = std::make_shared<std::string>(name);
    auto id = Sunnet::inst->NewService(t, args);

    return id;
}

void LuaAPI::KillService(int svrid)
{
    Sunnet::inst->KillService(svrid);
}

void LuaAPI::Send(int source, int to, sol::variadic_args args)
{
    auto msg = std::make_shared<ServiceMsg>();
    msg->m_source = source;
    msg->m_type = BaseMsg::TYPE::SERVICE;

    for (auto v : args)
    {
        msg->args.push_back(v);
    }

    Sunnet::inst->Send(to, msg);
}

void LuaAPI::Listen(int svrid, int port, const std::string& ip)
{
    Sunnet::inst->Listen(svrid, port, ip);
}

void LuaAPI::CloseConn(const std::string socket_uuid_str)
{
    boost::uuids::string_generator gen;
    boost::uuids::uuid uid = gen(socket_uuid_str);
    Sunnet::inst->CloseConn(uid);
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

bool LuaAPI::RegisterSvr(const std::string& svr_name, int svrid)
{
    if (svrid < 0) return false;

    auto moudle = Sunnet::inst->m_lua_["moudleSvr"];
    if(!moudle.valid())
    {
        Sunnet::inst->m_lua_.create_named_table("moudleSvr");
        printf("moudleSvr table created\n");
    }

    sol::table tb_moudleSvr = Sunnet::inst->m_lua_["moudleSvr"];
    tb_moudleSvr[svr_name] = svrid;

    return true;
}

int LuaAPI::GetSvrIdByName(const std::string& svr_name)
{
    auto moudle = Sunnet::inst->m_lua_["moudleSvr"];
    if(!moudle.valid() || moudle.get_type() != sol::type::table)
    {
        printf("moudleSvr table not created\n");
        return -1;
    }

    return moudle.get<sol::table>()[svr_name];
}

void LuaAPI::LoadSystemConfig(sol::state& lua)
{
    std::string file = "../server/system/system.lua";

    sol::protected_function_result result =lua.safe_script_file(file.c_str());

    if (!result.valid())
        BOOST_ASSERT_MSG(false, "load system config error");
}
