local queue = {}
local modename = "queue"
_G[modename] = queue
package.loaded[modename] = queue

-- local metatable = {}
-- metatable.__index = function (t , k)
--     print("array metatable: yes")
--     if type(k) == "string" and k == "array" then
--         error("can not index array")
--         return
--     end

--     return t[k]
-- end

-- setmetatable(queue, metatable)
-- local m_array = {}
-- metatable.array = m_array


function queue:new(t)
    t = t or {}
    t.array = {}
    setmetatable(t, self)
    self.__index = function (t, k)
        if type(k) == "string" and k == "array" then
            error("can not index array")
            return
        end
        return self[k]
    end
    return t
end

function queue:pushfront(v)
    v = v or 0
    local array  = rawget(self,"array")
    assert(array, "array is empty")

    table.insert(array, 1, v)
end

function queue:pushback(v)
    v = v or 0
    local array  = rawget(self,"array")
    assert(array, "array is empty")
    table.insert(array, v)
end

function queue:popfront()
    local array  = rawget(self,"array")
    assert(array, "array is empty")
    table.remove(array, 1)
end

function queue:popback()
    local array  = rawget(self,"array")
    assert(array, "array is empty")
    table.remove(array, #array)
end

function queue:front()
    local array  = rawget(self,"array")
    assert(array, "array is empty")

    return array[1]
end

function queue:back()
    local array  = rawget(self,"array")
    assert(array, "array is empty")

    return array[#array]
end

function queue:print()
    local array  = rawget(self,"array")
    assert(array, "array is empty")
    for k, v in ipairs(array) do
        print(k, v)
    end
end

return queue

