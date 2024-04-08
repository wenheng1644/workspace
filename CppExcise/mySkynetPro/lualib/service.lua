local skynet = require("skynet")
local cluster = require("skynet.cluster")

local M = {
    name = "",
    id = 0,

    exit = nil,
    init = nil,

    resp = {},
    client = {},
}

local dispatch = function(session, address, cmd, ...)
    local func = M.resp[cmd]
    skynet.error("M.name = " .. M.name .. ", M.id = " .. M.id .. ", service dispatch: cmd --> " .. cmd)
    if not func then
        skynet.ret()
        skynet.error("M.name = " .. M.name .. ", M.id = " .. M.id .. ", not the func --> " .. cmd)
        return
    end

    local ret = table.pack(xpcall(func, traceback, address, ...))
    local isok = ret[1]

    if not isok then 
        skynet.ret()
        return
    end

    -- skynet.error("print the ret: " .. cmd .. " = " .. cmd)
    -- for k, v in ipairs(ret or {}) do
    --     local txt = string.format("[cmd = %s]: k = %s, v = %s", cmd, k, v)
    --     skynet.error(txt)
    -- end

    skynet.retpack(table.unpack(ret, 2))
end


function init()
    skynet.error("M.name = " .. M.name .. ", M.id = " .. M.id)
    skynet.dispatch("lua", dispatch)
    if M.init then
        M.init()
    end
end

function traceback(err)
    skynet.error(tostring(err))
    skynet.error(debug.traceback())
end

function M.start(name, id, ...)
    M.name = name
    M.id = tonumber(id)

    skynet.start(init)
end


function M.call(node, srv, ...)
    local mynode = skynet.getenv("node")

    if node == mynode then
        return skynet.call(srv, "lua", ...)
    else
        return cluster.call(node, srv, ...)
    end
end

function M.send(node, svr, ...)
    local mynode = skynet.getenv("node")

    if node == mynode then
        return skynet.send(svr, "lua", ...)
    else
        return cluster.send(node, svr, ...)
    end
end

return M