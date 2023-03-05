local M = {}

function M.sayHello()
    print("Hello Linux")
end

function M.displayInfo(name)
    name = name or "kuang hui xian"
    print("name = ", name)
    M.sayHello()
end

return M