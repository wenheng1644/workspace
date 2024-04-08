local skynet = require("skynet")
local s = require("service")


s.addrs = {}
s.resp.newservice = function(source, name, ...)
    local tb = table.pack(...)

    local mynode = skynet.getenv("node")
    skynet.error("##################nodemgr svr: cur node = " .. mynode)
    skynet.error("nodemgr: print arg --> " .. name .. ", " .. table.concat(tb, ", "))
    skynet.error("svr name = " .. tb[1] .. ", svrid = " .. tb[2])
    local srv = skynet.newservice(name, tb[1], tb[2])

    local mynode = skynet.getenv("node")
    s.send(mynode, srv, "regist_addr", "nodemgr", skynet.self())       --给agent服务注册节点管理器

    skynet.error("nodemgr: success to new a svr (return) -- > " .. name .. ", agent = " .. srv)
    return srv
end

s.resp.reqAddr = function(source, addrname)
    if not s.addrs[addrname] then
        local str = string.format( "nodemgr svr: id = %s, node = %s,  addrname = %s", s.id, skynet.getenv("node"), addrname)
        skynet.error(str)

        return
    end

    return s.addrs[addrname]
end

s.resp.regist_addr = function(source, addrname, addr)
    s.addrs[addrname] = addr
    skynet.error("nodemgr svr: id = " .. s.id .. ", regist " .. addrname .. " = " .. addr)
end

s.start(...)