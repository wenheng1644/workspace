//
// Created by wenheng on 23-4-22.
//

#include "CScriptSystem.h"


CScriptSystem* CScriptSystem::m_ScriptPtr = nullptr;

void CScriptSystem::load()
{
    m_luaState = sol::state();
    defCFunc(); //先导出Cpp函数


    luaL_openlibs(m_luaState);
    auto res = m_luaState.do_file(std::string(LUASCRIPTFILE));

    if(!res.valid())
    {
        sol::error err = res;
        std::cerr << "lua file load error: " << err.what() << std::endl;
        exit(-1);
    }
}

void CScriptSystem::defCFunc()
{
    m_luaState.new_usertype<dataInfo>("dataInfo", sol::constructors<dataInfo()>(),
                    "ip", &dataInfo::ip,
                    "name", &dataInfo::name,
                    "times", &dataInfo::times);

    m_luaState.new_usertype<netHead>("netHead", sol::constructors<netHead()>(),
                    "len", &netHead::len,
                    "version", &netHead::version,
                    "type", &netHead::type,
                    "checknum", &netHead::checknum,
                    "info", &netHead::info);

    m_luaState.new_usertype<netMsg>("netMsg", sol::constructors<netMsg>(),
                    "head", &netMsg::head,
                    "body", &netMsg::body);

    m_luaState.new_usertype<chatSession>("chatSession", sol::constructors<chatSession(boost::asio::io_service, chatRoom&, const std::string)>(),
            "name", sol::property(&chatSession::name, &chatSession::setname),
            "ip", &chatSession::ip,
            "port", &chatSession::port);

    m_luaState.new_usertype<SessionQueue>("SessionQueue", sol::default_constructor);
    m_luaState.new_usertype<netMsgQueue>("netMsgQueue", sol::default_constructor);

    m_luaState.new_usertype<chatRoom>("chatRoom", sol::default_constructor,
                                      "sessions", &chatRoom::m_Sessionqueue,
                                      "msgs", &chatRoom::m_Msgqueue);

    m_luaState.set_function("createFile", &fileFunc::createFile);
}

CScriptSystem::CScriptSystem()
{
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

    if(!isLuaFuncExist("lua_loadNetMsg"))
    {
        std::cerr << "lua_loadNetMsg is not exist" << std::endl;
        exit(-1);
    }
    sol::function func = m_luaState["lua_loadNetMsg"];
    sol::object obj;
    if(func.valid())
    {
        std::cout << "function valid~" << std::endl;
        obj = func.call();
    }

    if(obj.get_type() != sol::type::table)
    {
        std::cerr << "return value is not a table" << std::endl;
        exit(-1);
    }
    sol::table tb = obj;

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

bool CScriptSystem::isLuaFuncExist(const std::string &funcname)
{
    if(funcname.empty())
    {
        std::cerr << "funcname is empty..." << std::endl;
        return false;
    }

    auto v = m_luaState[funcname];

    if(v.get_type() != sol::type::function)
    {
        std::cerr << boost::format("lua function: %s is not exist...") % funcname << std::endl;
        return false;
    }
    return true;
}

//bool CScriptSystem::loadLuaGM(const std::string &funcname)
//{
//    if(!isLuaFuncExist(funcname))
//    {
//        return false;
//    }
//
//    m_luaState[funcname]();
//
//    return true;
//}

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

