//
// Created by �ĺ� on 2022/11/28.
//
//#include "lua.h"
#include "string"
#include "cstring"
#include "stdio.h"
#include "stdarg.h"
#include "boost/format.hpp"
#include <iostream>
//#include "lualib.h"
//#include "lauxlib.h"

#include "math.h"
#include "dirent.h"

#include "windows.h"

extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "cFunctionToLua.h"
#include "TestClass.h"

struct ColorTable
{
    char* name;
    unsigned char red, green, blue;
};

#define MAX_COLOR 255
//ColorTable g_Color[] = {
//        {"WHITE", 255, 255, 255},
//        {"RED", 255, 0,0},
//        {"GREEN", 0, 255, 0},
//        {"BLUE", 0,0,255},
//        {NULL, 0,0,0}
//};

void error(lua_State* L, const char* fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    lua_close(L);
    exit(EXIT_FAILURE);
}

void lua_StartFileEnv(lua_State* L, const char* filename)
{
    if(luaL_loadfile(L, filename) || lua_pcall(L, 0,0,0))
        error(L, "can not run config file: %s", lua_tostring(L, -1));

}

void testStack()
{
    lua_State * L = luaL_newstate();
    lua_pushboolean(L,1);
    lua_pushnumber(L, 10);
    lua_pushnil(L);
    lua_pushstring(L, "hello world");

    stackDump(L);

    lua_pushvalue(L, 4);
    stackDump(L);
//
//    lua_replace(L,2);
//    stackDump(L);
//
//    lua_settop(L, 6);
//    stackDump(L);
//
//    lua_rotate(L, 3,1);
//    stackDump(L);
//    lua_rotate(L, 3,2);
//    stackDump(L);
//    lua_rotate(L, 3,3);
//    stackDump(L);
    lua_rotate(L, 1, 2);
//    lua_insert(L, 1);
    stackDump(L);
//
//    lua_pushnumber(L, 222);
//    stackDump(L);
//
//    lua_rotate(L, 4, 2);
//    stackDump(L);
//
//    lua_remove(L, 6);
//
//    stackDump(L);
//
//    lua_settop(L, -5);
//    stackDump(L);
    lua_close(L);
}


int getGolbal(lua_State* L, const char* varName)
{
    int isNum, result;
    lua_getglobal(L, varName);
    result = (int) lua_tointegerx(L, - 1, &isNum);
    if(!isNum)
        error(L, "%s should be a number\n", varName);
    lua_pop(L,1);
    return result;
}

void loadGlobal(lua_State* L, const char* filename, int *len, int *width, int* height)
{
    if(luaL_loadfile(L, filename) || lua_pcall(L, 0,0,0))
        error(L, "can not run config file: %s", lua_tostring(L, -1));

    *width = getGolbal(L, "width");
    *len = getGolbal(L, "length");
    *height = getGolbal(L, "height");
}

int getTableFiled(lua_State* L, const char* key)
{
    int result, isNum;
    std::cout << "start:" << std::endl;
    stackDump(L);
    lua_pushstring(L, key);
    lua_gettable(L, -2);
    result = (int) lua_tointegerx(L, -1, &isNum);
    if(!isNum)
        error(L, "invaild key = %s", key);

    std::cout << "end:" << std::endl;
    stackDump(L);
    lua_pop(L, 1);

    std::cout << "pop:" << std::endl;
    stackDump(L);
    return result;
}

void loadTableFiled(lua_State* L, const char* filename)
{
    if(luaL_loadfile(L, filename) || lua_pcall(L, 0,0,0))
        error(L, "can not run config file: %s", lua_tostring(L, -1));

    lua_getglobal(L, "color");
    if(!lua_istable(L, -1))
        error(L, "is not a table");

    int red = getTableFiled(L, "red");
    int blue = getTableFiled(L, "blue");
    int green = getTableFiled(L, "green");

    std::cout << boost::format("red = %s, blue = %s, green = %s") % red % blue % green << std::endl;

}

void setColorFiled(lua_State* L, const char* key, int value)
{
    lua_pushstring(L, key);
    lua_pushnumber(L, value);
    lua_settable(L, -3);
}

//void setColorTable(lua_State* L, const char* filename)
//{
//    if(luaL_loadfile(L, filename) || lua_pcall(L, 0,0,0))
//        error(L, "can not run config file: %s", lua_tostring(L, -1));
//
//
//
//    int i = 0;
////    std:: cout << "test = " << g_Color[i].name << std::endl;
//    while(g_Color[i].name)
//    {
//        lua_newtable(L);
//        std::cout << boost::format("i = %d: set start, red = %s, green = %s, blue = %s, name = %s")\
//        % i % g_Color[i].red % g_Color[i].green % g_Color[i].blue % g_Color[i].name << std::endl;
//        setColorFiled(L, "red", 1);
//        setColorFiled(L, "green", 2);
//        setColorFiled(L, "blue", 3);
//        lua_setglobal(L, g_Color[i].name);
//
//        i++;
//    }
//}

void Lua_callback(lua_State* L, const char* filename)
{
    if(luaL_loadfile(L, filename) || lua_pcall(L, 0,0,0))
        error(L, "can not run config file: %s", lua_tostring(L, -1));

    lua_getglobal(L, "sayHello");
    lua_pushstring(L, "xwz");

    if(lua_pcall(L, 1, 1, 0) != LUA_OK)
        error(L, "callback lua is error");

    std::string s = lua_tostring(L, -1);
    if(s.empty())
        error(L, "lua function return error");

    std::cout << boost::format("return a lua_func value = %s") %s << std::endl;
    lua_pop(L,1);

}

void va_luaCall(lua_State* L, const char* func, const char* sig, ...)
{
    va_list vl;
    int arg_count, result_count;

    va_start(vl, sig);
    lua_getglobal(L, func);

    for(arg_count = 0; *sig; arg_count++)
    {
        luaL_checkstack(L, 1, "too many args");
        int isBreak = false;
        switch (*sig++)
        {
            case 'd':
                lua_pushnumber(L, va_arg(vl, double ));
                break;
            case 'i':
                lua_pushnumber(L, va_arg(vl, int));
                break;
            case 's':
                lua_pushstring(L, va_arg(vl, char *));
                break;
            case 'b':
                lua_pushboolean(L, va_arg(vl, int));
                break;
            case '>':
                isBreak = true;
                break;
            default:
                error(L, "invalid option %c", *(sig-1));

        }
        if(isBreak)
            break;
    }
    result_count = strlen(sig);

    if(lua_pcall(L, arg_count, result_count, 0) != LUA_OK)
        error(L, "lua_callback is error function = %s, msg = %s", func, lua_tostring(L, -1));

    result_count = -result_count;

    while(*sig)
    {
        switch (*sig++)
        {
            case 'd':
            {
                int isnum;
                double n = lua_tonumberx(L, -1, &isnum);
                if(!isnum)
                    error(L, "error type: d = %s", lua_tostring(L,-1));
//                *va_arg(vl, double *) = n;
                std::cout << boost::format("double number = %d") % n << std::endl;
                lua_pop(L,1);
                break;
            }
            case 'i':
            {
                int isnum;
                int n = lua_tointegerx(L, -1, &isnum);
                if(!isnum)
                    error(L, "error type: i = %s", lua_tostring(L,-1));
//                *(va_arg(vl, int *)) = n;
                std::cout << boost::format("inter number = %i") % n << std::endl;
                lua_pop(L, 1);
                break;
            }
            case 's':
            {
                const char* str = lua_tostring(L, -1);
                if(!str)
                    error(L, "error type: s = %s", lua_tostring(L, -1));

//                *va_arg(vl, const char ** ) = str;
                std::cout << boost::format("str = %s") %str << std::endl;
                lua_pop(L, 1);
                break;
            }
            case 't':
            {
                int i = 1;
                if(!lua_istable(L, -1))
                    error(L, "is not a table");

                while(true)
                {
                    lua_pushnumber(L, i++);
                    lua_gettable(L, -2);

                    if(lua_type(L, -1) == LUA_TSTRING)
                    {
                        const char* str = lua_tostring(L, -1);
                        if(!str)
                            break;
                        std::cout << boost::format("array %d = %s") % (i-1) % str << std::endl;
                        lua_pop(L, 1);
                    }
                    else if(lua_type(L, -1) == LUA_TNUMBER)
                    {
                        int isNum;
                        int value = lua_tonumberx(L, -1, &isNum);
                        if(!isNum)
                            break;

                        std::cout << boost::format("value %d = %d") % (i-1) % value << std::endl;
                        lua_pop(L, 1);
                    }
                    else if(lua_type(L, -1) == LUA_TNIL)
                    {
                        lua_pop(L, 1);
                        break;
                    }

                }
                lua_pop(L, 1);
                break;
            }
            default:
            {
                error(L, "error return type");
                break;
            }

        }

        result_count++;
    }

    va_end(vl);
}

void WriteFile(lua_State* L)
{
    std::string filename;
    std::cout << "enter your filename:" << std::endl;
    while(std::getline(std::cin, filename))
    {
        if(filename != "")
            break;
    }
    std::cout << "Get filename = " << filename << std::endl;
    std::string line;
    std::cout << "content:";
    while(std::getline(std::cin, line))
    {
        if(line == "q" || line == "Q")
        {
            std::cout << "break the input" << std::endl;
            break;
        }
        std::cout << boost::format("line = %s") % line << std::endl;
        line += "\n";
        va_luaCall(L, "lua_WriteFile", "ss", filename.data(), line.data());
        std::cout << "content:";
    }

    std::cout << boost::format("filename = %s is write done") % filename << std::endl;
}

void ReadFile_test(lua_State* L)
{
    std::string filename = "luaCall2.txt";
    va_luaCall(L, "lua_ReadFileContent", "s>istt", filename.data());
}


int l_sin(lua_State* L)
{
    double d = luaL_checknumber(L,1);
    lua_pushnumber(L, sin(d));
    std::cout << boost::format("l_sin(%d) = %d") % d % sin(d) << std::endl;
    return 1;
}



void Lua_Call()
{
    char buff[256] = {0};
    int error;
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_pushcfunction(L, l_dir);

    lua_setglobal(L, "listDir");
    while(fgets(buff, sizeof(buff), stdin) != nullptr)
    {
        error = luaL_loadstring(L, buff) || lua_pcall(L, 0 ,0,0);
        if(error)
        {
            fprintf(stderr, "%s\n", lua_tostring(L,-1));
            lua_pop(L,1);
        }
    }

    lua_close(L);
}

//注册表测试
void test_Res(lua_State* L)
{
    lua_pushstring(L, "hello world");
    std::cout << "first push string" << std::endl;
    stackDump(L);
    std::cout << "make a ref from stack" << std::endl;
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    stackDump(L);
    std::cout << boost::format("ref = %d") %ref << std::endl;

    std::cout << "get the vale of ref to stack : " << ref << std::endl;
    int v1 = lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    std::cout << "print the stack again: "<< v1 << std::endl;
    stackDump(L);
    v1 = lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    std::cout << "get ref from other stack again: " << v1 << std::endl;
    stackDump(L);
    luaL_unref(L, LUA_REGISTRYINDEX, ref);
    v1 = lua_rawgeti(L, LUA_REGISTRYINDEX, ref);
    std::cout << "unref is successful, try to get: " << v1 << std::endl;

    stackDump(L);
}

void test_Res2(lua_State* L)
{
    static std::string  key = "the key";
    lua_pushstring(L, "hello world");
    std::cout << "first push string: " << std::endl;
    stackDump(L);
    lua_rawsetp(L, LUA_REGISTRYINDEX, (void *)key.c_str());
    std::cout << "rawstep : " << std::endl;
    stackDump(L);
    lua_rawgetp(L, LUA_REGISTRYINDEX, (void*)key.c_str());
    std::cout << "rawgetp: " << std::endl;
    stackDump(L);
    lua_rawgetp(L, LUA_REGISTRYINDEX, (void*)key.c_str());
    std::cout << "rawgetp2: " << std::endl;
    stackDump(L);
}


int main(void)
{
//    char dir[256] = {0};
//    GetCurrentDirectory(256, dir);
//    std::cout << "current dir = " << dir << std::endl;
//    SetCurrentDirectory(".\\..");
//    GetCurrentDirectory(256, dir);
//    std::cout << "change dir = " << dir << std::endl;
//
//
//    TestClass t;
//    t.sayHello();
    lua_State * L = luaL_newstate();
    luaL_openlibs(L);
    loadCfunc(L);
//    test_Res2(L);
////    luaopen_mylib(L);
    lua_StartFileEnv(L, "..\\config\\conf1.lua");

//    testStack();
//    WriteFile(L);
//    lua_close(L);
    return 0;
}