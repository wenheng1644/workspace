//
// Created by wenheng on 23-4-22.
//

#include "CScriptSystem.h"


CScriptSystem* CScriptSystem::m_ScriptPtr = nullptr;

void CScriptSystem::load()
{
//    m_luaState.open_libraries(sol::lib::base, sol::lib::string, sol::lib::table, sol::lib::os, sol::lib::io);
    luaL_openlibs(m_luaState);
    auto res = m_luaState.safe_script_file(std::string(LUASCRIPTFILE));
    if(!res.valid())
    {
        sol::error err = res;
        std::cerr << "lua file load error: " << err.what() << std::endl;
        exit(-1);
    }
//    sol::function_result call_res = res.call();

//    if(!call_res.valid())
//    {
//        sol::error err = call_res;
//        std::cerr << "call lua file error: " << err.what() << std::endl;
//        exit(-1);
//    }
}

void CScriptSystem::defCFunc()
{
    m_luaState.new_usertype<dataInfo>("dataInfo", sol::constructors<dataInfo()>(),
                    "ip", &dataInfo::ip,
                    "name", &dataInfo::name);

    m_luaState.new_usertype<netHead>("netHead", sol::constructors<netHead()>(),
                    "len", &netHead::len,
                    "version", &netHead::version,
                    "type", &netHead::type,
                    "checknum", &netHead::checknum,
                    "info", &netHead::info);

    m_luaState.new_usertype<netMsg>("netMsg", sol::constructors<netMsg>(),
                    "head", &netMsg::head,
                    "body", &netMsg::body);

    m_luaState.set_function("createFile", &fileFunc::createFile);
}

CScriptSystem::CScriptSystem()
{
    defCFunc(); //先导出Cpp函数
    load();     //再加载lua文件
}

u_int CScriptSystem::port()
{
    sol::type t = m_luaState["luaAddrTab"].get_type();

    if(t != sol::type::table)
        return 8888;

    return m_luaState["luaAddrTab"]["port"];

}

std::string CScriptSystem::ip()
{
    sol::type t = m_luaState["luaAddrTab"].get_type();

    if(t != sol::type::table)
        return "127.0.0.1";

    return m_luaState["luaAddrTab"]["ip"];
}


void CScriptSystem::test_toLua(netHead ptr)
{
//    if(!ptr) return;

    std::cout << "test_toLua | calling" << std::endl;
    m_luaState["test_getuserdata"](ptr);
}

void CScriptSystem::clua_wirtefile(netMsg msg)
{
//    std::cout << "clua_wirtefile | call lua_writeFile...." << std::endl;
    m_luaState["lua_writeFile"](msg);
}

std::vector<netMsg> CScriptSystem::loadNetMsg()
{
    std::vector<netMsg> records;
    sol::table tb = m_luaState["lua_loadNetMsg"]();

    if(sol::type::table == tb.get_type())
    {
        std::cout << "tb is a table: " << tb.size() << std::endl;
    }
    else
    {
        std::cout << "tb is not a table " << std::endl;
    }
    for(int i = 1; i <= tb.size(); i++)
    {
        netMsg msg;
        std::string ip = tb[i]["ip"];
        std::string name = tb[i]["name"];
        u_int len = tb[i]["len"];
        u_int type = tb[i]["type"];
        u_int version = tb[i]["version"];
        u_int checknum = tb[i]["checknum"];
        std::string body = tb[i]["body"];
        size_t times = tb[i]["times"];

        msg.head.len = len;
        msg.head.checknum = checknum;
        msg.head.type = type;
        msg.head.version = version;
        msg.head.info.times = times;
        memcpy(msg.head.info.name, name.c_str(), strlen(name.c_str()) + 1);
        memcpy(msg.head.info.ip, ip.c_str(), strlen(ip.c_str()) + 1);
        memcpy(msg.body, body.c_str(), strlen(body.c_str()) + 1);
        records.push_back(msg);
    }

    return records;
}

void CScriptSystem::clua_wirtefile(const netMsgList &netMsgs)
{
    sol::table datas = m_luaState.create_table();
    int index = 1;
    for(auto msg : netMsgs)
    {
        sol::table info = m_luaState.create_table();
        info["ip"] = msg.head.info.ip;
        info["name"] = msg.head.info.name;
        info["times"] = msg.head.info.times;
        info["len"] = msg.head.len;
        info["type"] = msg.head.type;
        info["version"] = msg.head.version;
        info["checknum"] = msg.head.checknum;
        info["body"] = msg.body;
        datas[index++] = info;
    }
    m_luaState["lua_writeDatasToFile"](datas);
}


bool fileFunc::createFile(const std::string &filename)
{
    std::filesystem::path path(filename);
    if(!exists(path))
    {
        std::filesystem::path pre = path.parent_path();
        if(!exists(pre))
        {
            std::error_code ec;
            std::filesystem::create_directories(pre, ec);
            if(ec)
            {
                std::cerr << "createFile | message: " << ec.message() << std::endl;
                return false;
            }
        }

        std::ofstream outFile(filename);
        if(outFile.is_open())
        {
//            std::cout << "createFile | successfully " << std::endl;
            outFile.close();
            return true;
        }
        else
        {
//            std::cout << "createFile | fail " << std::endl;
            return false;
        }
    }
    return true;
}

//CScriptSystem::~CScriptSystem()
//{
//    if(m_ScriptPtr)
//        delete m_ScriptPtr;
//}

