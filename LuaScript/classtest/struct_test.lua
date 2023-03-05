package.path = package.path .. ";D:\\MyGitHub\\workspace\\LuaScript\\classtest\\?.lua"
local Link = require("link")
local Queue = require("queue")
local Stack = require("myStack")
local Queue2 = require("queue2")
require("stackP")

local function link_test()
    local root = Link:new()

    local curNode = root
    for i = 1, 10 do
        local node = Link:new({}, i * i)
        curNode:insert(curNode, node)
        curNode = curNode.next
    end

    root:print()

    local target = root
    for i = 1, 3 do
        target = target.next
    end

    print("cur target value = ", target.value)

    root:remove(target)

    print("remove --- print")
    root:print()
end


local function queue_test()
    local queue = Queue:new()
    local q2 = Queue:new()

    for i = 1, 10 do
        queue:pushback(i * i + 1)
    end

    queue:print()

    queue:pushfront(111)
    print("================")
    queue:print()

    print("q2 print")
    q2:print()
    if queue.array then 
        print("yes")
        for k,v in ipairs(queue.array) do
            print(k,v)
        end
    end


end

-- queue_test()

local function stack_test()
    local stack = Stack:new({}, {1,2,3,4,5,6})
    print("stack size = ", stack:size())
    stack:printList()

    stack:push(222)
    print("====================")
    stack:printList()
    print("stack = ", stack)
    -- if stack.data then
    --     print("yes")
    -- end
end

-- stack_test()

-- g_var = 1000

-- print("rawget = ", rawget(_G, "g_var"))
local function queue_array()
    local queue1 = Queue:new()
    local queue2 = Queue:new()

    print("queue1 print:")
    queue1:print()

    print("queue2 print:")
    queue2:print()
    for i = 1, 10 do
        queue1:pushback(i * i)
    end

    print("print again queue1 = ")
    queue1:print()

    print("print again queue2 = ")
    queue2:print()

end

-- queue_array()

local function test_queue2()
    local q = getQueue()
    print("q addr = ",q)
    for i = 1, 10 do
        q:push(i)
    end

    q:print()

    local q2 = getQueue()

    print("q2  = ")
    q2:print()

    if q2.array then
        print("yes")
    end
end

-- test_queue2()

local function readonly(t)
    local proxy = {}

    local mt = {
        __index = t,
        __newindex = function (_,k,v)
            error("can not access readonly table", 2)
        end,
    }

    setmetatable(proxy, mt)

    return proxy
end

-- local t = {a = 1,}
-- t = readonly(t)
-- print("t[a] = ", t["a"])
-- t["c"] = 1

local function track(t)
    local proxy = {}

    local mt = {
        __index = function (_, k)
            print(string.format("track access key = %s", k))
            return t[k]
        end,

        __newindex = function(_,k,v)
            print(string.format("track assign key = %s, value = %s", k,v))
            t[k] = v
        end,
    }

    setmetatable(proxy, mt)

    return proxy
end

-- local org = {name = "xwz", addr = "guangzhou"}
-- org = track(org)

-- print("org[name] = ", org["name"])
-- org["name"] = "khx"

local function sub(t1, t2)
    local res = {}
    local record = {}
    for _, v in ipairs(t2) do
        record[v] = (record[v] or 0) + 1
    end

    for _, v in ipairs(t1) do
        if not record[v] or record[v] == 0 then
            res[#res+1] = v
        else
            record[v] = record[v] - 1
        end
    end

    return res
end

-- local t1 = {1,2,2,2,3,4,5,6}
-- local t2 = {2,3,5,6}

-- setmetatable(t1, {__sub = sub})

-- local res = t1 - t2

-- for _,v in ipairs(res) do
--     print(v)
-- end

local function len(t)
    local cnt = 0
    for k in pairs(t) do
        cnt = cnt + 1
    end
    return cnt
end

-- local tlen = {a = 1, b =2}
-- setmetatable(tlen, {__len = len})
-- print("tlen = ", #tlen)


local function fileAsArray(file)
    local proxy = {}
    local fd = io.open(file, "rb")

    if not fd then
        error("file open error", 2)
    end

    local buff = {}
    local c = fd:read(1)
    while c do
        buff[#buff+1] = c
        c = fd:read(1)
    end

    local mt = {
        __index = buff,
        __newindex = function (_, k, v)
            if type(v) ~= "string" or #v > 1 then
                print(string.format("value type error, k = %s,v = %s",k,v))
                return buff[k]
            end
            print("change buff key,value", k, v)
            buff[k] = v
            local wfd = io.open(file, "wb")
            if wfd then
                local value = table.concat(buff)
                wfd:write(value)
                wfd:close()
            end
        end,
        __len = function() return #buff end,

        __pairs = function()
            return function(_, k)
                -- print("__pairs key = ", k)
                return next(buff, k)
            end
        end,
    }

    setmetatable(proxy, mt)
    fd:close()

    return proxy
end

-- local proxy = fileAsArray("test.txt")
-- print("proxy[1] = ", proxy[1])
-- for k, v in pairs(proxy) do
--     print(k,v)
-- end

-- proxy[1] = 'aaa'
-- print("===============")
-- for k, v in pairs(proxy) do
--     print(k,v)
-- end
-- print("#proxy = ", #proxy)
-- proxy[#proxy-2] = 'x'
-- proxy[#proxy-1] = 'w'
-- proxy[#proxy] = 'z'


local stack = StackP:new(nil, {1,2,3,4})
stack.printArray()

stack.push(22)
print("front = ", stack.front())

-- print(debug.getupvalue(stack.printArray,2))
if _G["test"] then
    print("in global")
end

if stack.test then
    print("in stack")
end