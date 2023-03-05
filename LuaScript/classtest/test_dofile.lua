
local function t_dofile(filename)
    local info = {}
    function entry (en)
        table.insert(info, en)
    end

    dofile(filename)

    for _, t in pairs(info) do
        local content = string.format("name = %s, sex = %6s, age = %s", t.name, t.sex, t.age)
        print(content)
    end
end

-- t_dofile("name.txt")

-- local n1 = 11.0
-- local n2 = 11
-- print("n1 type = " .. math.type(n1))
-- print("n2 type = " .. math.type(n2))


local typeTb = {integer = "%d", float = "%a`"}
local function t_serialize(o)
    local str = ""
    if type(o) =="nil" or type(o) == "number" or type(o) == "string" or type(o) == "boolean" then
        str = string.format("%q", o)
    end
    print("serilize value = " .. str)
end

-- t_serialize(77)

--遍历打印表结构
local function dump(o, level, n)
    local t = type(o)
    n = n or 1
    level = level or 2
    if t == "nil" or t == "number" or t == "string" or t == "boolean" then
        io.write(string.format("%q", o))
    elseif t == "table" then
        if level == 0 then
            local v = tostring(o)
            io.write("<", v, ">")
            return
        end
        io.write("{\n")
        for k, v in pairs(o) do
            io.write(string.rep('\t', n), k, " = ")
            dump(v, level - 1, n + 1)
            io.write(",\n")
        end
        io.write(string.rep('\t', n-1),"}")
    elseif t == "function" then
        local v = tostring(o)
        io.write("<",v, ">")
    else
        error("this key can't be serilize: " .. t)
    end
end

local t = {a = 1, b = 2, c = "hello world"}
local t2 = {
    {
        name = "xwz",
        age = 24,
        sex = "male",
        info = {
            addr = "guangzhou",
            phone = "13424070047",
            deep = {
                "khx",
                "lyy",
                "xzy",
                seriouly = {
                    "hello world",
                    func = function ()
                        print("seriouly")
                    end
                }
            }
        },
        func1 = function() print("hello world") end,
    },
    {
        name = "yyy",
        age = 23,
        sex = "female"
    }
}
-- dump(t2, 5)

-- local x = tostring(t_dofile)
-- print(x)

local function formatTab(tab, level, space)
    assert(type(tab) == "table",  "param is not table!!")
    level = level or 3
    space = space or 1

    if level == 0 then
        return "< " .. tostring(tab) .. " >"
    end

    local split_str = string.rep("\t", space)
    local pre_splitStr = string.rep("\t", (space - 1) or 0)
    local content = "{\n"

    for k, v in pairs(tab) do
        local str_key
        if type(k) == "number" or type(k) == "string" or type(k) == "boolean" then
            str_key = string.format("%q", k)
        elseif type(k) == "table" or type(k) == "function" then
            str_key = "< " .. tostring(k) .. " >"
        end

        local str_val
        if type(v) == "number" or type(v) == "string" or type(v) == "boolean" then
            str_val = string.format("%q", v)
        elseif type(v) == "table" then
            str_val = formatTab(v, level - 1, space + 1)
        elseif type(v) == "function" then
            str_val = "< " .. tostring(v) .. " >"
        end

        content = content .. split_str .. str_key .. " = " .. str_val .. ",\n"
    end
    content = content .. pre_splitStr .. "}"
    return content
end

local function t_dump(v, level, space)
    level = level or 3
    space = space or 1

    local t = type(v)

    if t == "nil" or t == "number" or t == "string" or t == "boolean" then
        print(string.format("%q", v))
    elseif t == "function" then
        print("< " .. tostring(v) .. " >")
    elseif t == "table" then
        print(formatTab(v, level, space))
    else
        error("cant be serilize")
    end
end

t_dump(t2)