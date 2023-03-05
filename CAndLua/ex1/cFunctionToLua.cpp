//
// Created by 文恒 on 2023/2/19.
//
#include "cFunctionToLua.h"

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

    //参数顺序调整
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



int luaopen_mylib(lua_State* L)
{
    luaL_newlib(L, mylib);
    return 1;
}

void registerFunc(lua_State * L,const char* funcname, CFunc p)
{
    lua_pushcfunction(L, p);
    lua_setglobal(L, funcname);
}

int myCounter(lua_State* L)
{
    int val = lua_tointeger(L, lua_upvalueindex(1));
    lua_pushinteger(L, ++val);
    lua_copy(L, -1, lua_upvalueindex(1));
    return 1;
}

int test_upvalue(lua_State* L)
{
    lua_pushinteger(L, 0);
    lua_pushcclosure(L, myCounter, 1);
    return 1;
}

void loadCfunc(lua_State* L)
{
    registerFunc(L, "c_dirs", l_dir);
    registerFunc(L, "c_dirs2", c_listDirs);
    registerFunc(L, "c_sum", sumDig);
    registerFunc(L, "c_pack", cPack);
    registerFunc(L, "c_reverse", cReverse);
    registerFunc(L, "c_foreach", cforeach);
    registerFunc(L ,"c_colsure", test_upvalue);
}