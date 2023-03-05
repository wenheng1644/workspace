//
// Created by нд╨Ц on 2023/2/19.
//

#ifndef EX1_CFUNCTIONTOLUA_H
#define EX1_CFUNCTIONTOLUA_H

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
#include "filesystem"

extern "C"{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

void stackDump(lua_State * L);

int l_dir(lua_State* L);
int c_listDirs(lua_State* L);

int sumDig(lua_State* L);
int cPack(lua_State* L);
int cReverse(lua_State* L);
int cforeach(lua_State* L);

int getWorkDir(lua_State* L);

int cforeach_map(lua_State* L);

int cSplitstr(lua_State* L);

int cUpper(lua_State* L);

int cConcat(lua_State* L);

int cFliter(lua_State* L);

int cTransliterate(lua_State* L);

static const struct luaL_Reg mylib [] = {
        {"c_dirs", l_dir},
        {"c_dirs2", c_listDirs},
        {"c_sum", sumDig},
        {"c_pack", cPack},
        {"c_reverse", cReverse},
        {"c_foreach", cforeach},
        {nullptr, nullptr},
};

int luaopen_mylib(lua_State* L);
typedef int(*CFunc)(lua_State*);


#endif //EX1_CFUNCTIONTOLUA_H
