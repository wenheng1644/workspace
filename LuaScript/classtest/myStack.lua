local myStack = {}
local modename = "myStack"
_G[modename] = myStack
package.loaded[modename] = myStack

m_data = {}
local metaTable = {}
metaTable.__index = function(t, k)
    print("come")
    if type(k) == "string" and k == "data" then
        error("can not index data")
        return
    end

    return metaTable[k]
end

metaTable.data = m_data
setmetatable(myStack, metaTable)

function myStack:new(t, list)
    t = t or {}
    setmetatable(t, self)
    self.__index = self
    list = list or {}

    for _, v in ipairs(list) do
        m_data[#m_data + 1] = v
    end
    print(string.format("myStack:new   (myStack = %s) (t = %s) (self = %s)", myStack, t,self))
    return t
end

function myStack:empty()
    return #m_data == 0
end

function myStack:front()
    if self:empty() then
        error("stack is empty")
        return
    end
    return m_data[1]
end

function myStack:pop()
    if self:empty() then
        error("stack is empty")
        return
    end

    return table.remove(m_data, 1)
end

function myStack:push(v)
    table.insert(m_data, 1,v)
end

function myStack:size()
    return #m_data
end

function myStack:printList()
    for k, v in ipairs(m_data) do
        print(k,v)
    end
    print("myStack, self", myStack,self)
end

return myStack
