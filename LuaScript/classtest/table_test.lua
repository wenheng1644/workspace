
local function unquie(t)
    local res = {}
    local check = {}
    for k, v in pairs(t) do
        if not check[v] then
            res[#res + 1] = v
            check[v] = true
        end
    end
    return res
end

local t = {1,1,1,2,3,4,5,6,6,6,4,3}

for k, v in pairs(unquie(t)) do
    print(k,v)
end

local function table_maxn(t)
    local max
    for k, v in pairs(t) do
        if not max then
            max = v
        else
            if v > max then
                max = v
            end
        end
    end
    return max
end
local strs = {"lyy", "khx", "xwz", "xzy", "xjj"}
print("max = ", table_maxn(strs))

local t1 = {}
t1[1.0] = 1
print("t1[1] = " ,t1[1])

local t2 = {
    x = "hello world",
    y = "hello linux",
    1,
    2,
    3,
}

local t2_test = {[1] = 1, [2] = 2, [4] = 3, [5] = 4,}

print(t2.x, t2.y, t2[1])
print(string.rep("*", 10))
print(string.format("#t2 = %d\t#t2_test = %d", #t2, #t2_test))

local t3 = {}
t3[-1] = -1
print("t3[-1] = ", t3[-1])

local t4 = {[1] = 1, [-1] = -1}
print("t4[1] = ", t4[1], " t4[-1] = ", t4[-1])
for k, v in ipairs(t4) do
    print(k,v)
end

local emp = {}

local res = (((a or emp).t or emp).t or emp).t
print(res)

local list1 = {1,2,3,4,5,6}
local elem =  table.remove(list1, 1)
print(string.format("elem = %s, #list1 = %d", elem, #list1))

local function test_mulArg(...)
    local agrs = {...}
    print("test args ================")
    for k, v in pairs(agrs) do
        print(k, v)
    end

    local packTable = table.pack(...)
    print("packtable n = ", packTable.n)
    
    for i = 1, packTable.n do
        print(packTable[i])
    end

    print("select num = ", select("#", ...))
    local p2 = table.pack(select(1, ...))
    for k, v in pairs(p2) do
        print(k,v)
    end

    print("select[4] = ", select(4, ...))

end

test_mulArg(1,2,3,nil,5,6)
