local skynet = require("skynet")
local runconfig = require("runconfig")


skynet.start(function()

    local id = skynet.self()
    skynet.error("[ " .. id  .. " ]: " .. "start main scripy!!!")
    skynet.error("[ " .. id .. " ]: print config = " .. runconfig.agentmgr.node1)

    local agentmgr = skynet.newservice("agentmgr", "agentmgr", 1)
    local nodemgr = skynet.newservice("nodemgr", "nodemgr", 1)
    -- skynet.error("11111111111111111111111111111111111111111111")
    local gateway = skynet.newservice("gateway", "gateway", 1)
    -- skynet.error("22222222222222222222222222222222222222222222")

    local login1 = skynet.newservice("login", "login", 1)
    -- skynet.error("33333333333333333333333333333333333333333333")

    local login2 = skynet.newservice("login", "login", 2)

    skynet.error("login1 addr = " .. login1 .. ", login2 addr = " .. login2 .. ", agentmgr addr = " .. agentmgr)
    skynet.send(gateway, "lua", "regist_addr", "login1", login1)
    skynet.send(gateway, "lua", "regist_addr", "login2", login2)
    skynet.send(gateway, "lua", "regist_addr", "agentmgr", agentmgr)

    skynet.send(login1, "lua", "regist_addr", "agentmgr", agentmgr)
    skynet.send(login2, "lua", "regist_addr", "agentmgr", agentmgr)

    skynet.send(agentmgr, "lua", "regist_addr", "nodemgr", nodemgr)
    skynet.exit()

end)