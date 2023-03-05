ip = "127.0.0.0"
port = "8888"

local function test_dirs(path)
    local dirs = c_dirs2(path or ".")

    print(string.rep("*", 10))
    for filename, size in pairs(dirs or {}) do
        print(string.format("name = %s, size = %d", filename, size))
    end
end

function main()
    local curDir = c_getworkdir()
    print(string.format("work dir = " .. curDir))

    -- local tb = {".", ".."}
    -- c_foreachMap(tb, test_dirs)
    --local str = "hello:world:ok:fuck"
    --local tb = cSplitstr(str, ":")
    --
    --for _, v in ipairs(tb or{}) do
    --    print(v)
    --end
    --test_dirs("..")

    local str = "hello world"
    local tb = {
        ["h"] = "=",
        ["o"] = "-",
        ["l"] = false,
    }
    res = cTransliterate(str, tb)
    print(res)
end

main()

