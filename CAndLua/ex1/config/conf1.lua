width = 10
height = 20
length = 20

color = {
    red = 111,
    blue = 222,
    green = 200,
}

function sayHello(name)
    local str = name .. ":\thello, welcome!!"
    print("## lua call ##" .. str)
    return str
end

function lua_printTimeZone(isGet)
    print("hello linux???")

    if isGet then
        local t = os.time()
        print(string.format("isGet = %s, type(isGet) = %s", isGet, type(isGet)))
        print("current time zone = " .. t)
        return t
    end
end

local TimeContent = {
    gaoZhong = "xu zi yong",
    daXue = "liu ye yi",
    biYe = "Zone",
}

function getTimeContent(timeStr)
    print("get a arg = ", timeStr, type(timeStr))
    return TimeContent[timeStr] or ""
end

function lua_WriteFile(filename, content)
    local fileIsExit = function()
        local fd = io.open(filename)
        if fd then
            fd:close()
            return true
        end

        return false
    end

    print(string.format("filename = %s, type(filename) = %s\ncontent = %s, type(content) = %s", filename, type(filename),
        content, type(content)))

    local fd
    if not fileIsExit() then
        fd = io.open(filename, "w")
    else
        fd = io.open(filename, "a")
    end

    assert(fd, string.format("filename = %s can't open", filename))

    if not content or content == "" then
        print("content is nil...")
        return
    end

    fd:write(content)

    fd:close()

    print("lua callback done")
end

function lua_ReadFileContent(filename)
    local fd = io.open(filename)
    assert(fd, string.format("filename = %s can't open", filename))

    print(string.format("filename = %s open", filename))
    local contents = {}
    local lens = {}
    local index = 1
    for line in fd:lines() do
        print(string.format("line%d: %s", index, line))
        index = index + 1
        table.insert(contents, line)
        table.insert(lens, #line)
    end

    fd:close()
    print(string.format("filename = %s done", filename))
    return contents, lens, "ok - 200", 200
end

function test_ldir()
    local list = listDir(".")

    for k, v in ipairs(list or {}) do
        print(k, v)
    end
    print("test_ldir is done")
end

function test_sum()
    local agrs = {}
    for i = 1, 10 do
        table.insert(agrs, i)
    end

    local sum = cSum(3, 4, 5, 1)
    print("the cSum = " .. sum)
end

function test_cpack()
    local tab = cPack("hello world", "hello linux", 520, 1314)

    for k, v in ipairs(tab) do
        print(k, v)
    end

    print(cReverse("fuck", "you", 123, 321))
end

local function myprint(k, v)
    local str = string.format("the key = %s and the value = %s", k, v)
    print(str)
end

function test_foreach()
    local tab = { "hello world", "hello cpp", "xu wei zhen" }
    cforeach(tab, myprint)
end

function test_cDirs()
    -- local mylib = require("mylib")
    local dirs = c_dirs2(".")
    
    for f, size in pairs(dirs or {}) do
        if size ~= 0 then
            print(string.format("filename = %s and size = %d", f, size))
        end
    end
end

function test_closure()
    local c = c_colsure()
    print(c(), c(), c(), type(c))
end
test_closure()
