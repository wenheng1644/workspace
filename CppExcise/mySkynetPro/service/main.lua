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

    local ad_node = runconfig.admin.node
    skynet.error("1111111111111111111111111111111111111111111111111")
    local the_admin
    if mynode == ad_node then
        local admin = skynet.newservice("admin", "admin", 0)
        the_admin = admin
        skynet.error("222222222222222222222222222222222222222222222222222")
    else
        skynet.error("333333333333333333333333333333333333333333333333333")

        local proxy_admin = cluster.proxy(ad_node, "admin")
        the_admin = proxy_admin
        skynet.error("444444444444444444444444444444444444444444444444")

    end

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
        skynet.name("agentmgr", svr)
    else
        local proxy = cluster.proxy(anode, "agentmgr")
        the_agentmgr = proxy
        skynet.name("agentmgr", proxy)

    end

    skynet.error("main script: agentmgr svr 地址 = " .. the_agentmgr)


    -- local admin = 

    local scenes = {}
    --scene服创建(需要给agentmgr注册所有scene地址！！！！！！！！)
    for nodeid, conf in pairs(runconfig.scene) do

        if mynode == nodeid then
            for _, sid in ipairs(conf) do
                local svr = skynet.newservice("scene", "scene", sid)
                skynet.name("scene" .. sid, svr)
                cluster.register("scene" .. sid, svr)
                local info = {
                    addr = svr,
                    name = "scene" .. sid,
                    node = mynode
                }
        
                table.insert(scenes, info)
            end
        else

        end
    end

    --注册各个服务地址
    for k, gatewayaddr in ipairs(gateway) do
        for k1, loginaddr in ipairs(login) do
            skynet.send(gatewayaddr.addr, "lua", "regist_addr", loginaddr.name, loginaddr.addr)
        end

        skynet.send(gatewayaddr.addr, "lua", "regist_addr", "agentmgr", the_agentmgr)

        --给管理服注册所有网关
        if mynode ~= runconfig.admin.node then
            -- cluster.send(runconfig.agentmgr.node ,the_agentmgr, "regist_addr", v.name, v.addr)
            cluster.send(runconfig.admin.node, the_admin, "regist_addr", mynode, gatewayaddr.name, gatewayaddr.addr)
            skynet.error("main script: 给另一个节点注册网关, name = " .. gatewayaddr.name .. ", addr = " .. gatewayaddr.addr .. ", admin node = " .. runconfig.admin.node)
        else
            skynet.send(the_admin, "lua", "regist_addr", mynode, gatewayaddr.name, gatewayaddr.addr)
            skynet.error("main script: 给当前节点注册网关, name = " .. gatewayaddr.name .. ", addr = " .. gatewayaddr.addr)
        end
    end

    for _, loginaddr in ipairs(login) do
        skynet.send(loginaddr.addr, "lua", "regist_addr", "agentmgr", the_agentmgr)
        skynet.send(loginaddr.addr, "lua", "regist_addr", "nodemgr", nodemgr)
    end

    skynet.send(the_agentmgr, "lua", "regist_addr", "nodemgr", nodemgr)
    skynet.send(nodemgr, "lua", "regist_addr", "agentmgr", the_agentmgr)

    for _, v in ipairs(scenes) do
        if mynode ~= runconfig.agentmgr.node then
            cluster.send(runconfig.agentmgr.node ,the_agentmgr, "regist_addr", v.name, v.addr)
            skynet.error("main script: 给另一个节点的agentmrg注册当前scene服务地址, id = " .. v.name .. ", addr = " .. v.addr)
        else
            skynet.error("main script: 给本节点的agentmrg注册当前scene服务地址, id = " .. v.name .. ", addr = " .. v.addr)
            skynet.send(the_agentmgr, "lua", "regist_addr", v.name, v.addr)
        end
    end


    skynet.send(the_admin, "lua", "regist_addr", anode, "agentmgr", the_agentmgr)
    -- skynet.exit()

end)