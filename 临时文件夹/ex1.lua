
function dump(tb, level)
    assert(type(tb) == "table", "tb must be a table")
    level = level or 1

    io.write("{\n")
    for k, v in pairs(tb) do
        if type(k) == "number" or type(k) == "string" then
            local str = string.rep("\t", level) .. "[" .. tostring(k) .. "]" .. " = "
            io.write(str)
        end

        if type(v) == "number" or type(v) == "string" or type(v) == "boolean" or type(v) == "function" then
            local str = tostring(v) .. ",\n"
            io.write(str)
        elseif type(v) == "table" then
            dump(v, level + 1)
        end
    end
    local str = string.rep("\t", level - 1) .. "},\n"
    io.write(str)
end

local tb = {
    name = "xwz",
    addr = "guangzhou",
    age = 24,
    info = {
        height = 168,
        ip = "hostlocal",
    },
    [1] = "what?",
    [2] = "the"
}

dump(tb)