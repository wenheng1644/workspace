ip = "127.0.0.0"
port = "8888"
package.cpath = package.cpath .. ";/home/wenheng/Desktop/workspace/CAndLua/luaCall/extra/cLua/lib/lib?.so"
local mylib = require("mylib")
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

    print("mylib type = ", type(mylib))

    for index, v in pairs(mylib) do
        print(index, v)
    end

    --print(package.cpath)
end

main()

