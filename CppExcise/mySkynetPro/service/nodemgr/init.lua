local skynet = require("skynet")
local s = require("service")

s.resp.newservice = function(source, name, ...)
    local tb = table.pack(...)
    skynet.error("nodemgr: print arg --> " .. name .. ", " .. table.concat(tb, ", "))
    skynet.error("svr name = " .. tb[1] .. ", svrid = " .. tb[2])
    local srv = skynet.newservice(name, tb[1], tb[2])

    skynet.error("nodemgr: success to new a svr (return) -- > " .. name)
    return srv
end

s.start(...)