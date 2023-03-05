package.path = package.path .. ";D:\\MyGitHub\\workspace\\LuaScript\\classtest\\?.lua"

local mod = require("myStack")

local stack = mod:new({}, {1,2,3,4,5})

-- stack:push(1)
-- stack:printList()

local function isList(t)
    local keyCnt = 0

    for k, v in pairs(t) do
        keyCnt = keyCnt + 1
    end

    return #t == keyCnt
end

local function mulTable(t, x)
    t = t or {}
    local sum = 0

    for k, v in ipairs(t) do
        sum = sum + v * math.pow(x, k -1)
    end

    return sum
end

local function copy(t1, res, index)
    for k , v in ipairs(t1) do
        table.insert(res, index + k - 1, v)
    end
end

local t1 = {22,33,44,55}
local t2 = {1,2,3,4,5,6,7}
copy(t1, t2, 3)

for k, v in ipairs(t2) do
    print(k, v)
end

local function tableConcat(t, sep)
    local str = ""
    sep = sep or ""
    for _, v in ipairs(t) do
        str = str .. v .. sep
    end

    return str
end

local tc = {1,2,3,4,5}
print(tableConcat(tc, " "))

local function mulreturn()
    return 1, 2, 3 
end

local a, b, c = (mulreturn())
print(a, b, c)