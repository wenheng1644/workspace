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
#include "../common/commonClass.h"

#include "filesystem"

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
    void clua_wirtefile(const netMsgList& netMsgs);
    std::vector<netMsg> loadNetMsg();
    ~CScriptSystem() = default;
    void load();

private:
    static CScriptSystem* m_ScriptPtr;

    sol::state m_luaState;

    CScriptSystem();
    void defCFunc();

};

//void getChatsTable(sol::table& t);
namespace fileFunc{
    bool createFile(const std::string& filename);
}

#endif //TEXT1_CSCRIPTSYSTEM_H
