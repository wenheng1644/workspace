-- Account = {balance = 0}
-- function Account.withdraw(v)
--     Account.balance = Account.balance - v
--     if Account.balance < 0 then
--         print("Account.balance < 0")
--     end
-- end

-- Account.withdraw(100)
-- print(Account.balance)

metaTable = {}

function metaTable:new(t, length, width, high)
    t = t or {}
    setmetatable(t, self)
    self.__index = self
    print("self = ", self)
    self.length = length or 0
    self.width = width or 0
    self.high = high or 0
    return t
end

function metaTable:printVol()
    if not self then
        print("self empty")
        return
    end
    print("vol = ", self.high * self.length * self.width)
end

function metaTable:printArea()
    print("area = ", self.length * self.width)
end

local obj = metaTable:new()
print("obj.length = ",obj.length)
print("obj.__index = ", obj.__index)
