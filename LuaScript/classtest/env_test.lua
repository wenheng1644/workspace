X = 1

-- for k, v in pairs(_G) do
--     print(k, " = " ,v)
-- end

-- local v = load("return X")()
-- print(v)

local function getfield(f)
    local v = _G

    for w in string.gmatch(f, "[%a_][%w_]*") do
        v = v[w]
    end
    return v
end

local function setfield(f, val)
    local v = _G

    for w , d in string.gmatch(f, "([%a_][%w_]*)(%.?)") do
        if d == "." then
            v[w] = v[w] or {}
            v = v[w]
        else
            v[w] = val
        end
    end
end

-- local recored = {}

-- setmetatable(_G, {
--     __newindex = function (t, k, v)
--         if not recored[k] then
--             recored[k] = true
--         end
--         rawset(t, k , v)
--     end,

--     __index = function (_, k)
--         if not  recored[k] then
--             error("not record..")
--         else
--             return nil
--         end
--     end

-- })

local function t_raw()
    local tab = {}
    tab.a = 1

    local recored = {}
    setmetatable(tab, {
        __newindex = function (t, k, v)
            print("come in1")
            if not recored[k] then
                recored[k] = true    
            end
            rawset(t, k, v)
        end,
        __index = function(t, k)
            print("come in2")
            if not recored[k] then
                error("this " .. k .. " no record")
            else
                return nil
            end
        end
    })

    tab.b = 333
    print(tab.b)
end

-- t_raw()



local function t_env()
    print("_G and _ENV", _G, _ENV)
    a = 1
    print("_G.a, _ENV.a = ", _G.a, _ENV.a)
    local newEnv = {}
    setmetatable(newEnv, {
        __index = _G
    })
    _ENV = newEnv
    _G.a = 2
    b = 3
    -- _G.print("_G.a, _ENV.a = ", _G.a, a)
    print("b, _G.b, _ENV.b = ", b, _G.b, _ENV.b)
    -- a = 222
    -- _G.print("_G.a, _ENV.a = ", _G.a, _ENV.a)
end

-- t_env()

local function checkfield(v)
    local ans = string.match(v, "[^%w_%.]")
    if ans then
        error("is not vaild...")
    end

    for w, d in string.gmatch(v, "([%a_][%w_]*)(%.?)") do
        print(w, d)
    end

end
local str = "hello.world"
checkfield(str)