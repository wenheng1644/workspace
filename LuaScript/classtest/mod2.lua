module(..., package.seeall)

function test_SayHello()
    print("hello linux")
end

function test_display(name)
    name = name or "xwz"
    test_SayHello()
end

return M