
local function repl(str)
    return string.reverse(str)
end

local function test(file)
    local fd = io.open(file, "r")
    assert(fd, "file can't open")
    local content = fd:read("a")
    -- print("type(content) = ", type(content))
    print("org content = \n", content)
    local res = string.gsub(content, "%w+", repl)

    print("print the res = \n",res)
    fd:close()
end

-- test("test.txt")

local function clouser(x)
    return {
        set = function (y) x = y end,
        get = function() return x end,
    }
end

local o1, o2 = clouser(100), clouser(200)

-- print(string.format("o1.get = %s, o2.get = %s", o1.get(), o2.get()))
-- o1.set(1)
-- o2.set(2)
-- print(string.format("twice: o1.get = %s, o2.get = %s", o1.get(), o2.get()))

local function split(str, del)
    local res = {}

    -- local i, j = 1,1
    -- i, j = string.find(str, del,i)

    -- local begin = 1
    -- while i do
    --     table.insert(res,string.sub(str,begin,i-1))
    --     i = j + 1
    --     begin = j + 1
    --     i,j = string.find(str, del, i)
    -- end

    local partten = "[^%s]+"

    for w in string.gmatch(str, partten) do
        table.insert(res, w)
    end

    return res
end

-- local str = "hello world   what are you   doing??"
-- local res = split(str, " ")

-- if res and next(res) then
--     for k, v in ipairs(res) do
--         print(k, v)
--     end
-- end

local function tranlste(str, tb)
    local func = function (key)
        if not tb[key] then return "" end
        return tb[key]
    end

    local res = string.gsub(str, "[%w%p]+", func)
    return res
end

-- local map = {}
-- for _, v in ipairs(res) do
--     map[v] = string.reverse(v)
-- end
-- -- map["you"] = nil

-- for key, value in pairs(map) do
--     print(key, value)
-- end

-- local recontent = tranlste(str, map)
-- print("org str = ", str)
-- print("after str = ", recontent)


local function totalCalc(file, n, splits)
    local fd = file and io.open(file, "r") or io.stdin
    assert(fd, string.format("fd can't not opne %s", file and file or "io.stdin"))

    splits = splits or {}
    local counts = {}

    for line in fd:lines() do
        for w in string.gmatch(line, "%w+") do
            --只记录长度大于四的单词且不在忽略列表中
            if #w >= 4 and not splits[w] then
                counts[w] = (counts[w] or 0) + 1
            end
        end
    end

    local words = {}
    for w in pairs(counts) do
        words[#words+1] = w
    end

    table.sort(words, function(w1, w2)
        if counts[w1] > counts[w2] then
            return true
        end
        return false
    end)

    n = n or 1
    n = n > #words and #words or n
    for i = 1, n do
        print(string.format("world: %s = count: %s", words[i], counts[words[i]]))
    end
    print(string.format("totoal world = %d", #words))
    print("program done")
end

-- totalCalc(nil, 222, {["girls"] = 1})

local function testShift()
    local x = 11

    print(string.format("%X ; %X ; %X ; %X", x, x << 3, x << 2, x << 1))
    print(string.format("%X ; %X", x >> -1, x >> 3))

    local y = -1
    print(string.rep("*", 10))
    print(string.format("%X ; %X ; %X", y, y << 1, y >> 63))

    print(0x81 < 0x1F, math.ult(0x81, 0x0F))
end

-- testShift()

local function testStringPack()
    -- local v = 3
    -- local s = string.pack("jj", v, 2)
    -- print("len(s) = ", #s)
    -- print("unpack = ", string.unpack("i", s, 9))

    local s1 = "hello"
    local str = string.pack("s3", s1)
    print("#str = ", #str)
    -- print("unpack(str) = ", string.unpack("bbb", str,6))
    -- print("unpack(str2) = ", string.unpack("s3", str, 6))

    -- for i = 1, #str do
    --     print("unpack(str) = ", string.unpack("b", str,i))
    -- end
    print("(len) = ", string.unpack("i3", str,1))

end

-- testStringPack()

local function packStr(str, packLen)
    local len = #str
    local fmt = string.format("s%d", packLen)
    local p_str = string.pack(fmt, str)
    print("pack str is done\t", str)

    for i = 1, packLen do
        print("unpack len bit: ", string.unpack("b", p_str, i))
    end

    local upack_len = string.unpack(string.format("i%d", packLen), p_str,1)
    local u_fmt = string.format("c%d", upack_len)

    local up_str = string.unpack(u_fmt, p_str, packLen+1)

    print("unpack str = ", up_str)
end

-- packStr("fuck you", 2)

local function bitOrder()
    local x = 13
    local s1 = string.pack("i4", x)

    print(string.rep("*", 10))
    for i = 1, #s1 do
        print("unpack s1 byte = ", string.unpack("b", s1, i))
    end

    print(string.rep("*", 10))

    local s2 = string.pack(">i4",x)
    for i = 1, #s2 do
        print("unpack s1 byte = ", string.unpack("b", s2, i))
    end


    print(string.rep("*", 10))

    local s3 = string.pack("<i4",x)
    for i = 1, #s3 do
        print("unpack s1 byte = ", string.unpack("b", s3, i))
    end
end

-- bitOrder()

local function readbyte(filename)
    local fd = io.open(filename, "rb")
    assert(fd, "file cant open")

    local blocksize = 16

    for bytes in fd:lines(blocksize) do
        for i = 1, #bytes do
            local b = string.unpack("B", bytes, i)
            -- print(string.format("%02X", b))
            io.write(string.format("%02X ", b))
        end
        print(string.rep(" ", blocksize - #bytes))
        bytes = string.gsub(bytes, "%c", ".")
        print(" ", bytes)
    end
end

readbyte("./classtest/tempTest.lua")