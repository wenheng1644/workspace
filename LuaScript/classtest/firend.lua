-- local module = {}

firend = {}

function firend:new(t, name, age, sex)
    t = t or {}
    setmetatable(t, self)
    self.__index = self
    self.name = name or ""
    self.age = age or 18
    self.sex = sex or "female"

    return t
end

function firend:print()
    print("info = ", self.name, self.age, self.sex)
end

bestFirend = firend:new()

function bestFirend:new(t, nice)
    t = t or {}
    setmetatable(t, self)
    self.__index = self
    self.nice = nice or 10

    return t
end

return firend