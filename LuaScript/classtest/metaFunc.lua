local myTable = {}
local secondTable = {}

metaTable = {
    __index = secondTable,
    __newindex = secondTable,
    __call = function(t, ...)
        local args = {...}
        for k, v in pairs(args) do
            print("k~v: ", k, v)
        end
    end
}

setmetatable(myTable, metaTable)
-- print("myTable's high = ", myTable.high)
myTable["a"] = 1
print("myTable[a]", myTable["a"])

if(not myTable) then
    print("yes")
end

myTable(1,2,3,4,5,6,7)
