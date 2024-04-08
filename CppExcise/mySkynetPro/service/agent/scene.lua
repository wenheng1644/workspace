local skynet = require("skynet")
local s = require "service"
local runconfig = require("runconfig")

local mynode = skynet.getenv("node")

s.snode = nil
s.sname = nil

-- local str = string.format("################################################### agent_enter s addr  = %s", s)
-- skynet.error(str)

-- s.client = s.client or {}
local function random_scene()
    local nodes = {}

    for nid in pairs(runconfig.scene) do
        table.insert(nodes, nid)

        if runconfig.scene[mynode] then
            table.insert(nodes, nid)
        end
    end

    local node_idx = math.random(1, #nodes)
    local node = nodes[node_idx]

    local scene_idx = math.random(1, #runconfig.scene[node])
    local sceneid = runconfig.scene[node][scene_idx]

    return node, sceneid
end



s.client.enter = function(msg)
    if s.sname then
        return {"enter", 1, "已在场景"}
    end

    skynet.error("agent svr: to enter -- > s.id = " .. s.id)

    local snode, sid = random_scene()
    local sname = "scene" .. sid

    skynet.error("agent svr: snode = " .. snode .. ", sid = " .. sid)
    -- for k, v in pairs(s.addrs or {}) do
    --     skynet.error("####################### print the addrs: k = " .. k .. ", v = " .. v)
    -- end
    local addr = s.addrs[sname]
    if not addr then
        addr = skynet.call(s.addrs["agentmgr"], "lua", "reqAddr", sname)
        -- addr = s.call(runconfig.agentmgr.node, s.addrs["agentmgr"], "reqAddr", sname)
        if not addr then
            skynet.error("agent svr: id = " .. s.id .. ", 无法获取指定服务地址... " .. sname)
            return {"enter", 1, "无法获取指定服务地址"}
        end
        s.addrs[sname] = addr
    end

    local isok = s.call(snode, addr, "enter", s.id, skynet.self(), mynode)
    skynet.error("agent svr: done!!!!!!!!!!!!!!!")
    local str = string.format("@agent_enter svr: print the agent table addr  = %s", s)
    skynet.error(str)

    if not isok then
        return {"enter", 1, "进入失败"}
    end

    s.snode = snode
    s.sname = s.addrs[sname]

    return {"enter", 0, "开始进入场景"}
end

s.client.shift = function(msg)
    skynet.error("agent_game svr: start to shift")
    if not s.sname then return end

    local x = msg[2] or 0
    local y = msg[3] or 0
    skynet.error("agent_game svr: sname = " .. s.sname .. ", snode = " .. s.snode .. ", move --> x = " .. x .. ", y = " .. y)


    s.call(s.snode, s.sname, "shift", s.id, x, y)

    return {"shift", x, y}
end

s.leave_scene = function()
    if not s.sname then return end

    s.call(s.snode, s.sname, "leave", s.id)

    skynet.error("#### agent_game svr: playerid = " .. s.id .. ", leave the scene")

    s.sname = nil
    s.snode = nil
end

-- skynet.error("###############################agent.scene服务###############################")
-- for k, v in pairs(s.client or  {}) do
--     skynet.error("$$$$$$$$$$$$$$$$$$$$$$$$$ k = " .. k)
-- end