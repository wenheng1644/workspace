//
// Created by �ĺ� on 2023/2/19.
//
#include "cFunctionToLua.h"
#include "string.h"

void stackDump(lua_State * L)
{
    int i;
    int top = lua_gettop(L);

    for(i = 1; i <= top; ++i)
    {
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING:
                std::cout << boost::format("(string)i = %d: %s") % i % lua_tostring(L,i) << std::endl;
                break;
            case LUA_TBOOLEAN:
                std::cout << boost::format("(bool)i = %d: %s") %i % (lua_toboolean(L,i) ? "true" : "false") << std::endl;
                break;
            case LUA_TNUMBER:
                std::cout << boost::format("(number)i = %d: %g") % i % lua_tonumber(L,i) << std::endl;
                break;
            case LUA_TTABLE:
                std::cout << boost::format("(table)i = %d") % i << std::endl;
                break;
            case LUA_TFUNCTION:
                std::cout << boost::format("(function)i = %d") %i << std::endl;
                break;
            default:
                std::cout << boost::format("(other)i = %d: %s") % i % lua_type(L,i) << std::endl;
                break;
        }
    }
    printf("\n");
}

extern "C"{

int l_dir(lua_State* L)
{
    DIR* dir;
    dirent* entry;
    int i;
    const char* path = luaL_checkstring(L, 1);

    if(!path)
    {
        lua_pushnil(L);
        lua_pushstring(L, strerror(errno));
        return 2;
    }

    lua_newtable(L);
    i = 1;
    dir = opendir(path);
    while((entry = readdir(dir)) != nullptr)
    {
        lua_pushnumber(L, i++);
        lua_pushstring(L, entry->d_name);
        lua_settable(L, -3);
    }

    closedir(dir);
    return 1;
}

int c_listDirs(lua_State* L)
{
    int argcnt = lua_gettop(L);
    if(argcnt != 1)
    {
        std::cerr << "arg cnt must be 1" << std::endl;
        exit(-1);
    }

    const char* pathname = luaL_checkstring(L, -1);
    if(!pathname || std::string(pathname) == "")
    {
        std::cerr << "pathname is error" << std::endl;
        exit(-1);
    }
    using namespace std::filesystem;
    path curpath(pathname);

    if(!exists(curpath))
    {
        std::cerr << boost::format("not a path name = %s") % curpath.string() << std::endl;
        return 0;
    }

    directory_iterator iteor(curpath);
    lua_pop(L, 1);
    lua_newtable(L);
//    stackDump(L);
    for(auto& enter : iteor)
    {
        lua_pushstring(L, enter.path().string().c_str());
        if(enter.is_directory())
        {
            lua_pushinteger(L, 0);
        }
        else
        {
            lua_pushnumber(L, enter.file_size());
        }
        lua_settable(L, 1);
//        stackDump(L);
    }

    return 1;
}

int sumDig(lua_State* L)
{
    int top = lua_gettop(L);
    if(top <= 1)
    {
        std::cout << boost::format("not other args: %d") % top << std::endl;
        return 0;
    }

    double sum = 0;
    for(int i = top; i >= 1; --i)
    {
        double v = luaL_checknumber(L, i);
        sum += v;
        lua_pop(L, 1);
    }
    lua_pushnumber(L, sum);
    return 1;
}

int cPack(lua_State* L)
{
    lua_newtable(L);
    int top = lua_gettop(L);
//    stackDump(L);
    lua_insert(L, 1);
//    stackDump(L);

    //����˳�����
    int insertIndex = 2;
    for(int i = 1; i < top; i++)
    {
        lua_insert(L, insertIndex++);
    }

    int index = 1;
    for(int i = top; i > 1; --i)
    {
        lua_pushinteger(L, index++);
        int top2 = lua_gettop(L);
//        lua_rotate(L, top2, 2);
        lua_insert(L, top2-1);
//        stackDump(L);
        lua_settable(L, 1);
    }
    return 1;
}

int cReverse(lua_State* L)
{
    int top = lua_gettop(L);
    if(top == 0)
    {
        std::cerr << "top = 0" << std::endl;
        return 0;
    }

    int index = 1;
    for(int i = 1; i <= top; ++i)
    {
        lua_insert(L, index++);
    }
//    stackDump(L);
//    lua_next()
    return top;
}

int cforeach(lua_State* L)
{
    int top = lua_gettop(L);
    if(top != 2)
    {
        std::cerr << "must be 2 args" << std::endl;
        exit(-1);
    }

    if(!lua_isfunction(L, -1))
    {
        std::cerr << "second arg is not function" << std::endl;
        exit(-1);
    }

    if(!lua_istable(L,-2))
    {
        std::cerr << "first arg is not table" << std::endl;
        exit(-1);
    }

    lua_pushnil(L);
    while(lua_next(L, 1))
    {
        int curTop = lua_gettop(L);
        lua_settop(L, curTop + 2);
        lua_copy(L, -3, -1);
        lua_copy(L, -4, -2);
        lua_copy(L, 2, -3);

        lua_pcall(L, 2, 0, 0);
    }

    return 0;
}

int getWorkDir(lua_State* L)
{
    char dir[256] = {0};
    getcwd(dir, sizeof(dir));
//    std::cout << "current dir = " << dir << std::endl;

    lua_pushstring(L, dir);

    return 1;
}

int cforeach_map(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TFUNCTION);

    int len = luaL_len(L, 1);

    for(int i = 1; i <= len; ++i)
    {
        lua_pushvalue(L, 2);
        lua_geti(L, 1, i);
        lua_call(L, 1, 1);
        lua_seti(L, 1, i);
    }

    return 0;
}

int cSplitstr(lua_State* L)
{
    const char* cstr = luaL_checkstring(L, 1);
    const char* partten = luaL_checkstring(L, 2);

    char* target = nullptr;

    lua_newtable(L);
    int index = 1;
    std::string stdstr(cstr);
    char* str = stdstr.data();
    while((target = strchr(str, *partten)) != nullptr)
    {
        lua_pushlstring(L, str, target - str);
        lua_seti(L, -2, index++);
        str = ++target;
    }

    lua_pushstring(L, str);
    lua_seti(L, -2, index);

    return 1;
}

int cUpper(lua_State* L)
{
    size_t luaStrLen;
    luaL_Buffer b;
    const char* str = luaL_checklstring(L, 1, &luaStrLen);
    char* p = luaL_buffinitsize(L, &b, luaStrLen);

    for(int i = 0; i < luaStrLen; i++)
    {
        p[i] = toupper(u_char(str[i]));
    }
    luaL_pushresultsize(&b, luaStrLen);
    return 1;
}

int cConcat(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    size_t len = luaL_len(L, 1);

    const char* spacer = nullptr;
    if(lua_gettop(L) == 2)
        spacer = luaL_checkstring(L, 2);

    luaL_Buffer b;
    luaL_buffinit(L, &b);
    for(int i = 1; i <= len; ++i)
    {
        lua_geti(L, 1, i);
        if(spacer && i != len)
        {
            const char* cstr = lua_tostring(L, -1);
            std::string  str = std::string(cstr) + std::string(spacer);
            lua_pop(L, 1);
            lua_pushstring(L, str.c_str());
        }

        luaL_addvalue(&b);
    }
    luaL_pushresult(&b);
//    LUA_REGISTRYINDEX
    return 1;
}

int cFliter(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TFUNCTION);

    int tableLen = luaL_len(L, 1);
    lua_newtable(L);
    int index = 1;
    for(int i = 1; i <= tableLen; ++i)
    {
        lua_pushvalue(L, 2);
        lua_geti(L, 1, i);
        lua_pcall(L, 1, 1, 0);
        luaL_checktype(L, -1, LUA_TBOOLEAN);
        bool res = lua_toboolean(L, -1);
        lua_pop(L, 1);
        if(res)
        {
            lua_geti(L, 1, i);
            lua_seti(L, 3, index++);
        }
    }
    return 1;
}

//int cTransliterate(lua_State* L)
//{
//    const char* cstr = luaL_checkstring(L, 1);
//    luaL_checktype(L, 2, LUA_TTABLE);
//
//    std::string str(cstr);
//    std::string res = str;
//
//    for(auto& c : str)
//    {
//        int type = lua_getfield(L, 2, std::string(1, c).c_str());
//        auto lam = [c](char x)
//        {
//            if(x == c)
//                return true;
//            return false;
//        };
//        if(type == LUA_TBOOLEAN)
//        {
//            bool status = lua_toboolean(L, -1);
//            if(!status)
//            {
//                auto iter = std::remove_if(res.begin(), res.end(), lam);
//                res.erase(iter, res.end());
//            }
//        }
//        else if(type == LUA_TSTRING)
//        {
//            const char* replaceStr = lua_tostring(L, -1);
//            std::replace_if(res.begin(), res.end(), lam, *replaceStr);
//        }
//        lua_pop(L, 1);
//    }
//    lua_pushstring(L, res.c_str());
//    return 1;
//}

static const struct luaL_Reg mylib [] = {
        {"c_dirs", l_dir},
        {"c_dirs2", c_listDirs},
        {"c_sum", sumDig},
        {"c_pack", cPack},
        {"c_reverse", cReverse},
        {"c_foreach", cforeach},
        {"c_getworkdir", getWorkDir},
        {"c_foreachMap", cforeach_map},
        {"cSplitstr", cSplitstr},
        {"cUpper", cUpper},
        {"cConcat", cConcat},
        {"cFliter", cFliter},
//        {"cTransliterate", cTransliterate},
        {nullptr, nullptr},
};

int luaopen_mylib(lua_State* L)
{
    luaL_newlib(L, mylib);
    return 1;
}
}
