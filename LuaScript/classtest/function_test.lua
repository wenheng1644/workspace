
local function deltavie(f, del)
    del = del or 1e-4
    return function (x)
        return (f(x + del) - f(x)) / del;
    end
end

print("1e-4 = ", 1e-4)
print("os.time() = ", os.time())

math.randomseed(os.time())