
local function say(k)
    -- print("hello world")
    for i = 1, k do
        print("i = ", i)
        coroutine.yield()
    end
end

local function t_cor()
    -- local co = coroutine.create(say)
    -- print(coroutine.status(co))
    -- print(coroutine.resume(co, 2))
    -- print(coroutine.status(co))
    -- print(coroutine.resume(co))
    -- print(coroutine.status(co))
    -- print(coroutine.resume(co))
    -- print(coroutine.status(co))
    -- print(coroutine.resume(co))
    -- print(coroutine.status(co))

    local co2 = coroutine.create(function (a,b)
        coroutine.yield(a+2, b+4)
    end)

    -- print(coroutine.status(co2))

    -- print(coroutine.resume(co2, 5, 9))

    local co3 = coroutine.create(function(x)
        -- print("print the x = ", x)
        -- print("print the yield = ", coroutine.yield())
        return coroutine.yield()
    end)

    print(coroutine.resume(co3, "hello world"))
    print(coroutine.resume(co3, "hello linux"))
    print(coroutine.resume(co3, "hello linux2"))
    print(coroutine.resume(co3, "hello linux3"))
end

t_cor()