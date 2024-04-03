local skynet = require("skynet")
local runconfig = require("runconfig")
local skynet_manager  = require("skynet.manager")
local cluster = require("skynet.cluster")


skynet.start(function()

    local id = skynet.self()
    skynet.error("[ " .. id  .. " ]: " .. "start main script!!!")
    skynet.error("[ " .. id .. " ]: print config = " .. runconfig.agentmgr.node)

    -- local agentmgr = skynet.newservice("agentmgr", "agentmgr", 1)
    -- local nodemgr = skynet.newservice("nodemgr", "nodemgr", 1)

    -- local gateway = skynet.newservice("gateway", "gateway", 1)

    -- local login1 = skynet.newservice("login", "login", 1)

    -- local login2 = skynet.newservice("login", "login", 2)

    -- skynet.error("login1 addr = " .. login1 .. ", login2 addr = " .. login2 .. ", agentmgr addr = " .. agentmgr)
    -- skynet.send(gateway, "lua", "regist_addr", "login1", login1)
    -- skynet.send(gateway, "lua", "regist_addr", "login2", login2)
    -- skynet.send(gateway, "lua", "regist_addr", "agentmgr", agentmgr)

    -- skynet.send(login1, "lua", "regist_addr", "agentmgr", agentmgr)
    -- skynet.send(login2, "lua", "regist_addr", "agentmgr", agentmgr)

    -- skynet.send(agentmgr, "lua", "regist_addr", "nodemgr", nodemgr)

    local mynode = skynet.getenv("node")
    local nodecfg = runconfig[mynode]

    local nodemgr = skynet.newservice("nodemgr", "nodemgr", 0)
    -- skynet.name()
    cluster.reload(runconfig.cluster)
    cluster.open(mynode)
    skynet.error("!!!!!!!!!!!!!!!!!!!!!!!node = " .. mynode .. ": the nodemgr = " .. nodemgr)

    local gateway = {}
    --网关服创建
    for k, v in ipairs(nodecfg.gateway or {}) do
        local svr = skynet.newservice("gateway", "gateway", k)
        local info = {
            addr = svr,
            name = "gateway" .. k
        }
        gateway[k] = info
    end

    local login = {}
    --登录服务创建
    for k, v in ipairs(nodecfg.login or {}) do
        local svr = skynet.newservice("login", "login", k)

        local info = {
            addr = svr,
            name = "login" .. k
        }
        login[k] = info
    end

    local anode = runconfig.agentmgr.node

    local the_agentmgr
    --全局agent管理服务创建
    if mynode == anode then
        local svr = skynet.newservice("agentmgr", "agentmgr", 0)
        the_agentmgr = svr
    else
        local proxy = cluster.proxy(anode, "agentmgr")
        the_agentmgr = proxy
    end


    --注册各个服务地址
    for k, gatewayaddr in ipairs(gateway) do
        for k1, loginaddr in ipairs(login) do
            skynet.send(gatewayaddr.addr, "lua", "regist_addr", loginaddr.name, loginaddr.addr)
        end

        skynet.send(gatewayaddr.addr, "lua", "regist_addr", "agentmgr", the_agentmgr)
    end

    for _, loginaddr in ipairs(login) do
        skynet.send(loginaddr.addr, "lua", "regist_addr", "agentmgr", the_agentmgr)
        skynet.send(loginaddr.addr, "lua", "regist_addr", "nodemgr", nodemgr)
    end

    skynet.send(the_agentmgr, "lua", "regist_addr", "nodemgr", nodemgr)

    skynet.exit()

end)