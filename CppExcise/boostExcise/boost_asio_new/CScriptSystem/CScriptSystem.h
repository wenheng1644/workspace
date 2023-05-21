//
// Created by wenheng on 23-4-22.
//

#ifndef TEXT1_CSCRIPTSYSTEM_H
#define TEXT1_CSCRIPTSYSTEM_H

#include "string"
#include "iostream"
#include "fstream"

#include "sol/sol.hpp"
#include "boost/format.hpp"

#include "../netMsg/netMsg.h"
#include "../common/commonClass.h"
#include "../chat/chatRoom.h"

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

    template<typename T, typename... ArgsT>
    bool loadLuaGM(const T& name, ArgsT... args);

    template<typename T> void setCFunc(const std::string& funcName, T f);
private:
    static CScriptSystem* m_ScriptPtr;

    sol::state m_luaState;

    CScriptSystem();
    void defCFunc();
    bool isLuaFuncExist(const std::string& funcname);

};

//void getChatsTable(sol::table& t);
namespace fileFunc{
    bool createFile(const std::string& filename);
}

template<typename T>
void CScriptSystem::setCFunc(const std::string &funcName, T f)
{
    m_luaState.set_function(funcName, f);
}

template<typename T, typename... ArgsT>
bool CScriptSystem::loadLuaGM(const T &name, ArgsT... args) {
    if(!isLuaFuncExist(name)) return false;

    std::cout << "CScriptSystem::loadLuaGM | size params = " << sizeof...(args) << std::endl;
    m_luaState[name](args...);
}

#endif //TEXT1_CSCRIPTSYSTEM_H
