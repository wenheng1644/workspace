ip = "127.0.0.0"
port = "8888"
local prefixPath = "/home/wenheng/Desktop/workspace/CAndLua/luaCall/extra"
local cLUAPATH = ";" .. prefixPath .. "/cLua/lib/lib?.so"
local transPATH = ";" .. prefixPath .. "/transLib/lib/lib?.so"
local uptransPATH = ";" .. prefixPath .. "/uptransLib/lib/lib?.so"
package.cpath = package.cpath ..cLUAPATH .. transPATH .. uptransPATH
package.loaded["translib"] = nil
package.loaded["mylib"] = nil
local mylib = require("mylib")
local translib = require("translib")
local uptranslib = require("uptranslib")
local function test_dirs(path)
    local dirs = c_dirs2(path or ".")

    print(string.rep("*", 10))
    for filename, size in pairs(dirs or {}) do
        print(string.format("name = %s, size = %d", filename, size))
    end
end

function main()
    local curDir = mylib.c_getworkdir()
    print(string.format("lua: work dir = " .. curDir))
    --print(package.cpath)

    local tb = {
        ["h"] = "w",
        ["o"] = "-",
        ["l"] = false,
    }


    --translib.settrans(tb)
    --translib.gettrans()
    --
    --if transtb then
    --    for k, v in pairs(transtb) do
    --        print(k, v)
    --    end
    --end

    --print("mylib.cTransliterate = ", mylib.cTransliterate)
    --print("translib.transliterate = ", translib.lua_transliterate)
    --print("translib.settrans = ", translib.settrans)
    local str = "hello world, hello linux"
    --for k, v in pairs(translib) do
    --    print(k, v)
    --end

    --local res = translib.lua_transliterate(str)
    --print(res)
    --print("print the uptranslib: ")
    --for k, v in pairs(uptranslib) do
    --    print(k, v)
    --end

    uptranslib.upSettrans(tb)
    local tb2 = uptranslib.upGettrans()
    if not tb2 then
        print("tb2 is nil")
    elseif not next(tb2) then
        print("tb2 is no data")
    end
    for k, v in pairs(tb2) do
        print(k, v)
    end
    print(uptranslib.upTransliterate(str))
end

main()

