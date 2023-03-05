
local function myPari(array)
    local index = 0

    return function ()
        index = index + 1
        if array[index] then
            return index, array[index]
        end
    end
end

local t1 = {"hello", "world", "fuck", "you"}

-- for k, v in myPari(t1) do
--     print(k,v)
-- end
local f1 = myPari(t1)
local f2 = myPari(t1)
print(f1())
print(f1())
print(f2())