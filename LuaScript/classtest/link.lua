
link = {}
local modName = "link"
_G[modName] = link
setmetatable(link, _G)

package.loaded[modName] = link

function link:new(t, v)
    t = t or {}
    setmetatable(t, self)
    self.__index = self

    t.value = v or 0
    t.next = nil

    return t
end


function link:insert(node, t)
    local nodeNext = node.next

    node.next = t
    t.next = nil
    if nodeNext then
        t.next = nodeNext
    end
    -- return self
end

function link:remove(node)
    local curNode = self
    local preNode = nil
    while curNode do
        if curNode == node then
            if not preNode then
                self = self.next
                return self
            end

            preNode.next = curNode.next
            curNode = nil
            return self
        end
        preNode = curNode
        curNode = curNode.next
    end
end

function link:print()
    local curNode = self

    while curNode do
        print("value = ", curNode.value)
        curNode = curNode.next
    end
end


return link