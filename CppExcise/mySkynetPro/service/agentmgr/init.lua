local skynet = require("skynet")
local s = require("service")
local runconfig = require("runconfig")

STATUS = {
    LOGIN = 2,
    GAME = 3,
    LOGOUT = 4,
}

local players = {}
local addrs = {}

function mgrplayer()
    local m = {
        playerid = nil,
        node = nil,
        agent = nil,
        status = nil,
        gate = nil,
    }
    return m
end

local function getonlinecount()
    local n = 0
    for playerid in pairs(players) do
        n = n + 1
    end

    return n
end


s.resp.reqlogin = function(source, playerid, node, gate, nodemgr)
    local mplayer = players[playerid]
    skynet.error("agentmgr : playerid = " .. playerid .. ", node = " .. node .. ", gate = " ..gate)
    if mplayer and mplayer.status == STATUS.LOGOUT then
        skynet.error("reqlogin fail, at status LOGOUT: " .. playerid)
        return false
    end

    if mplayer and mplayer.status == STATUS.LOGIN then
        skynet.error("reqlogin fail, at status LOGIN: " .. playerid)
        return false
    end

    if mplayer then
        local pnode = mplayer.node
        local pagent = mplayer.agent
        local pgate = mplayer.gate
        mplayer.status = STATUS.LOGOUT
        skynet.error("the account was login....  we need to kick out game")

        s.call(pnode, pagent, "kick")
        s.send(pnode, pagent, "exit")
        s.send(pnode, pgate, "send", playerid, {"kick", "other login"})
        s.call(pnode, pgate, "kick", playerid)
    end

    local player = mgrplayer()
    player.playerid = playerid
    player.node = node
    player.gate = gate
    player.status = STATUS.LOGIN

    player.agent = nil


    players[playerid] = player
    skynet.error("agentmgr: start to call nodemgr --> nodemgr svr = " .. nodemgr .. ", from node = " .. node)
    local agent = s.call(node, nodemgr, "newservice", "agent", "agent", playerid)
    s.send(node, agent, "regist_addr", "agentmgr", skynet.self())

    -- for k, v in pairs(runconfig.scene) do
    --     for _, id in ipairs(v) do
    --         local secne_name = "scene" .. id
    --         s.send(node, agent, "regist_addr", secne_name, addrs[secne_name])
    --     end
    -- end

    skynet.error("agentmgr svr: create a new agent = " .. agent)
    skynet.error("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@")
    player.agent = agent
    player.status = STATUS.GAME

    skynet.error("agentmgr: success to login!!!!")
    return true, agent
end

s.resp.reqkick = function(source, playerid, reason)
    local mplayer = players[playerid]
    if not mplayer then return false end

    skynet.error("##############################agentmgr: recv request: playerid = " .. playerid .. ", status = " .. mplayer.status)
    if mplayer.status ~= STATUS.GAME then return false end

    local pnode = mplayer.node
    local pagent = mplayer.agent
    local pgate = mplayer.gate
    mplayer.status = STATUS.LOGOUT

    s.call(pnode, pagent, "kick")
    s.send(pnode, pagent, "exit")
    s.send(pnode, pgate, "send", playerid, {"kick", reason})
    s.send(pnode, pgate, "kick", playerid)
    players[playerid] = nil

    return true
end

s.resp.regist_addr = function(source, addrname, addr)
    addrs[addrname] = addr

    skynet.error("&&&&&&&&&&agentmgr: success to regist addrname = " .. addrname .. ", addr = " .. addr)
end

s.resp.reqAddr = function(source, addrname)
    if not addrs[addrname] then
        skynet.error("agentmgr svr: 请求的addrname = " .. addrname .. " 不存在")
        return
    end

    return addrs[addrname]
end

s.resp.shutdown = function (source, kicknum)
    local count = getonlinecount()

    local n = 0
    skynet.error("agentmgr svr: shutdown server, to kick online player: " .. kicknum)
    for playerid , player in pairs(players) do
        skynet.fork(s.resp.reqkick, nil, playerid, "close server")
        n = n + 1

        if n >= kicknum then
            break
        end
    end


    while true do
        skynet.sleep(100)
        local new_count = getonlinecount()
        skynet.error("agentmgr svr: now online count = " .. new_count)
        if new_count <= 0 or new_count <= count - kicknum then
            return new_count
        end
    end
    
end

s.start(...)