
local function test_assert(a, b)

    if type(a) ~= "number" or type(b) ~= "number" then
        error("args is not number")
    end

    return a+b
end

if xpcall(test_assert, function(err) print(debug.traceback("test_assert call error")) end,1,2) then
    print("pcall yes")
else
    print("pcall no")

end