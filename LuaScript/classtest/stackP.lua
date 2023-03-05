local StackP = {}
local modename = "StackP"
_G[modename] = StackP
package.loaded[modename] = StackP


function test()
    print("test---")
end

function StackP:new(t, datas)
    t = t or {}
    local array = {}

    t.push = function(v) table.insert(array,1,v) end
    t.pop = function()
        assert(array and next(array), "table is empty")
        table.remove(array, 1)
    end
    t.front = function()
        assert(array and next(array), "table is empty")
        return array[1]
    end
    t.isEmpty = function ()
        return next(array) ~= nil
    end

    t.printArray = function ()
        if array and next(array) then
            for k,v in ipairs(array) do
                print(k,v)
            end
        end
    end

    if datas and next(datas) then
        for _, v in ipairs(datas) do
            t.push(v)
        end
    end

    return t
end

