
local function listTable(t, i)
    i = i + 1
    local v = t[i]
    print("i = ", i)
    if v then
        return i, t[i]
    end
end

local t = {"xwz", "khx", "lyy"}

local function myPair(table)
    return listTable, table, 0
end

-- for k, v in myPair(t) do
--     print(k, v)
-- end

local function create(n)
    local function foo1()
        print(n)
    end

    local function foo2()
        n = n + 10
    end

    return foo1, foo2
end

-- local n = 1
-- local f1, f2 = create(n)
-- f1()
-- f2()
-- f1()
-- f2()
-- print("&f1 = ", f1)
-- local t1, t2 = create(n)
-- print("=======================")
-- t1()
-- t2()
-- t1()
-- t2()
-- print("&t1 = ", t1)

local function testClose(n)
    local function f_close1()
        local function f1()
            print(n)
        end

        local function f2()
            n = n + 10
        end
        return f1, f2
    end
    return f_close1
end

-- local f_cl = testClose(1)

-- local f_iner_a1, f_iner_a2 = f_cl()
-- f_iner_a1()
-- f_iner_a2()
-- f_iner_a1()
-- f_iner_a2()
-- print("&f_iner_a1 = ", f_iner_a1)
-- print("----------------")
-- local f_iner_b1, f_iner_b2 = f_cl()
-- f_iner_b1()
-- f_iner_b2()
-- f_iner_b1()
-- f_iner_b2()
-- print("&f_iner_b1 = ", f_iner_b1)

-- print("=================")
-- local test2 = testClose(1)
-- local f2_iner_a1, f2_iner_a2 = test2()
-- f2_iner_a1()
-- f2_iner_a2()
-- f2_iner_a1()
-- f2_iner_a2()

local function fromto(n, m, space)
    assert(n <= m, "m must great than n")
    local i = n
    space = space or 1
    local iter = function (m)
        if i <= m then
            i = i + space
            return i - space
        end
    end

    return iter, m
end

-- for i in fromto(1, 10) do
--     print("the i = ", i)
-- end

-- for i in fromto(3, 9, 2) do
--     print("the i2 = ", i)
-- end

local function uniqueWord(file)
    local i = 0
    local words = {}
    for lines in io.lines(file) do
        for word in string.gmatch(lines, "%w+") do
            words[word] = (words[word] or 0) + 1
        end
    end

    local res = {}
    for word, cnt in pairs(words) do
        if cnt == 1 then
            res[#res+1] = word
        end
    end
    local iter = function ()
        i = i + 1
        if res[i] then
            return i, res[i]
        end
    end
    return iter
end

-- for k, v in uniqueWord("test.txt") do
--     print(k, v)
-- end

local function iterWords(file,func)
    assert(type(func) == "function", "func not a function")
    assert(type(file) == "string" and file ~= "", "need a filename")

    for lines in io.lines(file) do
        for word in string.gmatch(lines, "%w+") do
            func(word)
        end
    end
end

local words = {}
iterWords("test.txt", function (w)
    print(w)
    words[w] = (words[w] or 0) + 1
end)
