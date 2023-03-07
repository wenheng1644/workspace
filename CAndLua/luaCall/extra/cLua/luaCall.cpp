//
// Created by �ĺ� on 2023/2/13.
//

#include "luaCall.h"

luaCall* luaCall::m_luaCallobj = nullptr;

luaCall::luaCall() : m_luaState(luaL_newstate()) {
    luaL_openlibs(m_luaState);
//    loadCfunc();

    if(luaL_loadfile(m_luaState, LUAPATH) || lua_pcall(m_luaState, 0, 0 ,0))
        luaL_error(m_luaState, "error to create luaCall: %s", lua_tostring(m_luaState, -1));
}

void luaCall::vCall(const char *funcname, ...) {
    if(!funcname)
        return;

    int status = lua_getglobal(m_luaState, funcname);

    if(lua_isfunction(m_luaState, -1))
        printError(m_luaState, "not a function: %s", lua_tostring(m_luaState, -1));

    va_list args;
    va_start(args, funcname);
    va_end(args);


}

std::string luaCall::getLuaVarByKey(const char *key) {
    if(!key)
        printError(m_luaState, "key is empty: %s", key);

    lua_getglobal(m_luaState, key);
    if(lua_type(m_luaState, -1) != LUA_TSTRING)
        printError(m_luaState, "is not a string");

    std::string var = lua_tostring(m_luaState, -1);

    lua_pop(m_luaState, 1);

    return var;
}

void luaCall::registerFunc(const char *funcname, CFunc p) {
    lua_pushcfunction(m_luaState, p);
    lua_setglobal(m_luaState, funcname);
}

//void luaCall::loadCfunc() {
//    registerFunc("c_dirs", l_dir);
//    registerFunc( "c_dirs2", c_listDirs);
//    registerFunc("c_sum", sumDig);
//    registerFunc( "c_pack", cPack);
//    registerFunc( "c_reverse", cReverse);
//    registerFunc("c_foreach", cforeach);
//    registerFunc("c_getworkdir", getWorkDir);
//    registerFunc("c_foreachMap", cforeach_map);
//    registerFunc("cSplitstr", cSplitstr);
//    registerFunc("cUpper", cUpper);
//    registerFunc("cConcat", cConcat);
//    registerFunc("cFliter", cFliter);
//    registerFunc("cTransliterate", cTransliterate);
//}

void luaCall::run() {

}

void luaCall::loadEnv() {

}
