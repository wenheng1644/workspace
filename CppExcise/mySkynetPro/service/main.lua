local skynet = require("skynet")
local runconfig = require("runconfig")


skynet.start(function()

    local id = skynet.self()
    skynet.error("[ " .. id  .. " ]: " .. "start main scripy!!!")
    skynet.error("[ " .. id .. " ]: print config = " .. runconfig.agentmgr.node1)
    
    local gateway = skynet.newservice("gateway", "gateway", 1)
    local login1 = skynet.newservice("login", "login", 1)
    local login2 = skynet.newservice("login", "login", 2)

    skynet.error("login1 addr = " .. login1 .. ", login2 addr = " .. login2)
    skynet.send(gateway, "lua", "regist_addr", "login1", login1)
    skynet.send(gateway, "lua", "regist_addr", "login2", login2)

    skynet.exit()

end)