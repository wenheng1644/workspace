//
// Created by wenheng on 23-4-22.
//

#ifndef TEXT1_CSCRIPTSYSTEM_H
#define TEXT1_CSCRIPTSYSTEM_H

#include "string"
#include "iostream"
#include "fstream"

#include "sol/sol.hpp"

#include "../netMsg/netMsg.h"

#include "filesystem"

#define LUASCRIPTFILE "../luaScript/main.lua"
//管理lua
class CScriptSystem {
public:
    static CScriptSystem* getSingalton()
    {
        if(!m_ScriptPtr)
            m_ScriptPtr = new CScriptSystem;
        return m_ScriptPtr;
    }

    u_int port();
    std::string ip();

    void test_toLua(netHead ptr);
    void clua_wirtefile(netMsg msg);
    std::vector<netMsg> loadNetMsg();
private:
    static CScriptSystem* m_ScriptPtr;

    sol::state m_luaState;

    CScriptSystem();
    void load();
    void defCFunc();

};

//void getChatsTable(sol::table& t);
namespace fileFunc{
    bool createFile(const std::string& filename);
}

#endif //TEXT1_CSCRIPTSYSTEM_H
