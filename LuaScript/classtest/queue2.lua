-- local __queue = {}


-- function __queue:new(t)
--     t = t or {}
--     setmetatable(t, self)
--     self.__index = self
--     t.array = {}
--     return t
-- end

-- local queue = __queue:new()
-- if queue.array then
--     print("queue have array")
-- else
--     print("queue no have array")
-- end

local queue = {}
local modename = "queue2"
_G[modename] = queue
package.loaded[modename] = queue

function queue:new(t)
    t = t or {}
    setmetatable(t, self)
    self.__index = self
    t.array = {}
    print("org table array", t)
    return t
end

function queue:push(v)
    local array = rawget(getmetatable(self) , "array")
    if array then
        table.insert(array,  v)
    else
        print("can not push")
    end
end

function queue:pop()
    local array = rawget(getmetatable(self), "array")
    if array then
        table.remove(array, 1)
    end
end

function queue:print()
    local array = rawget(getmetatable(self), "array")

    -- if queue == self then
    --     print("queue == self")
    -- else
    --     print("queue != self")
    -- end

    -- if __queue == self then
    --     print("__queue == self")
    -- else
    --     print("__queue != self")
    -- end
    -- print("queue, __queue, self", queue, __queue, self)
    print("self, getmetatable(self)", self, getmetatable(self))
    if array then
        for k, v in ipairs(array) do
            print(k,v)
        end
    else
        print("no")
    end
end

function getQueue()
    local t = {}
    local queue = queue:new()
    setmetatable(t, queue)
    queue.__index = function (t, k)
        if type(k) == "string" and k == "array" then
            error("can not index array")
            return
        end
        return queue[k]
    end

    return t
end
