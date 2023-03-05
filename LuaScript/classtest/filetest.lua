local function fileOp(filename)
    local f = io.open(filename, "a+")
    if not f then
        print(string.format("file = %s can not open", filename))
        return
    end
    io.output(f)
    local date = os.date("%Y-%m-%d %H:%M:%S")
    if not date then
        print("date is nil")
        io.close(f)
        return
    end
    print("file write done")
    io.write(date)
    io.close(f)
end

-- fileOp("filecontent.txt")

local function readLineFile(filename)
    local f = io.open(filename, "r")
    if not f then
        print("file can not open")
        return
    end

    -- io.input(f)
    -- local bytes = f:seek("end")
    -- print(string.format("all bytes = %s", bytes))
    -- local str = f:read(5)
    print(string.format("now bytes = %s, last content = %s", f:seek("cur", 20), f:read("*a")))
    -- for v in f:lines() do
    --     print(v)
    -- end

    print(string.format("file = %s read done", filename))
    io.close(f)
end

local function searchword(line, mod)
    local ans = {}
    for w in string.gmatch(line, mod) do
        ans[#ans+1] = w
        print(w)
    end
    return ans
end

local function fileMod(filename)
    local f = io.open(filename, "r")
    if not f then
        print("file can't open")
        return
    end

    local mod = ".*(liu).*"
    local index = 1
    for line in f:lines() do
        local t = searchword(line, mod)
        if next(t) then
            local str = string.format("row = %s: ", index) .. table.concat(t, " ")
            print(str)
            index = index + 1
        end
    end

    f:close()
    print("Its done")
end

-- fileMod("test.txt")

local function lua_findstr(line, str)
    local beg = 1
    local i,j =string.find(line, str, beg)
    local cnt = 0
    while(i) do
        cnt = cnt + 1
        local findstr = string.sub(i, j)
        print(string.format("cnt = %s: %s (%s. %s)",cnt, findstr, i, j))
        beg = j+1
        i,j =string.find(line, str, beg)
    end

    if cnt == 0 then
        print("can't find it str = ", str)
    end
    print("done")
end
local line = "hello world, hello linux\nI like you kuang hui xian, hello girls"

-- lua_findstr(line, "girls")

local function test_match(line, mod)

    local args = {string.match(line, mod)}
    for k, v in pairs(args) do
        print(k , v)
    end

end
os
test_match(line, "kuang (%w%w%w) (%w%w%w%w)")