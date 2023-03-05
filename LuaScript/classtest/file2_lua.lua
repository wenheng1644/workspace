
local function fileread()
    local f = io.input("test.txt")
    if not f then
        error("file can not open")
        return
    end

    for w in f:lines() do
        print(w)
    end

    io.write()
end

-- fileread()

local function filewirte()
    print("input your file name =")
    local filename = io.read()
    local f = io.output(filename)
    if not f then
        error("file can not open")
        return
    end

    local line = io.read()
    while line and #line > 0 do
        print("cur line = ", line)
        f:write(line, "\n")
        line = io.read()
    end
    f:close()
end

-- filewirte()

local function readNum()
    local f = io.input("./classtest/read_num.txt")
    if not f then 
        error("file can not open")
        return
    end

    local n1 = io.read("n")
    print("n1 = ", n1)
    while n1 do
        print(n1)
        n1 = io.read("n")
    end
end

-- readNum()
local function file_assert()
    local msg = io.stdin:read()
    io.stderr:write(msg)

    io.tmpfile()

    
end

-- file_assert()

local function sysCall()
    local cmd = io.stdin:read()
    print("cmd = ", cmd)

    -- local res = os.execute(cmd)

    -- if res then
    --     print("success call")
    -- else
    --     print("fail to call")
    -- end

    local f = io.popen(cmd, "r")
    if not f then return end

    local cnt = 0
    for w in f:lines() do
        cnt = cnt + 1
        print(string.format("line %d = %s", cnt, w))
    end
end

-- sysCall()

local function sortFile(file1, file2)
    local f1 = file1 and io.open(file1, "r")
    local f2 = file2 and io.open(file2, "w") or io.stdout
    f1:seek()
    print(string.rep("*",10))
    if not f1 or not f2 then
        error("file can not open")
        return
    end

    print(string.rep("=",10))
    local contents = {}

    local line = f1:read()
    print("line = ", line)
    while line do
        contents[#contents+1] = line
        print(string.format("line %d = %s", #contents, line))
        line = f1:read()
    end


    print(string.rep("-",10))
    table.sort(contents, function(line1, line2)
        if line1 < line2 then
            return true
        end
        return false
    end
    )
    print(string.rep("+",10))
    for _, v in ipairs(contents) do
        f2:write(v,"\n")
    end

    f1:close()
    f2:close()
    print("done!!")
end

-- sortFile("test.txt", "./classtest/sortFile.txt")

local function readTest(file)
    local f = file and io.open(file) or io.stdin
    if not f then return end

    local line = f:read()
    while line do
        print(line)
        line = f:read()
    end
    f:close()
end
-- readTest("test.txt")

local function readLastLineFromFile(file, n)
    local f = io.open(file, "r")
    if not f then
        error("file can not open")
        return
    end

    n = n or 1
    f:seek("end")
    local toBegBytes
    for i = 1, n do
        repeat
            toBegBytes = f:seek("cur", -1)
            local c = f:read(1)
            f:seek("cur", -1)
            print("i = ", i, toBegBytes, c)
            if c == "\n" then
                print("eq to \\n")
            end
            -- if c == "\n" then
            --     f:seek("cur", -1)
            -- end
        until c == "\n" or toBegBytes == 0

        if toBegBytes == 0 then break end

    end
    if toBegBytes ~= 0 then
        f:seek("cur", 2)
    end
    local getRes = f:read("a")

    f:close()
    print("cur contents = ", getRes)
end

readLastLineFromFile("test.txt",2)