
local function derivative(f, num)
    num = num or 1e-5
    return function(x)
        return (f(x+num) - f(x)) / num
    end
end

print("sin(1)", math.sin(1))
print("sin'(1)", derivative(math.sin)(1))