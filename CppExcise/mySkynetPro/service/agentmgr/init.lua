local skynet = require("skynet")
local s = require("service")

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
    -- skynet.send(agent, "lua", "regist_addr", "agentmgr", skynet.self())
    s.send(node, agent, "regist_addr", "agentmgr", skynet.self())
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
    s.send(pnode, pgate, "kick", playerid)
    players[playerid] = nil

    return true
end

s.resp.regist_addr = function(source, addrname, addr)
    addrs[addrname] = addr

    skynet.error("agentmgr: success to regist addrname = " .. addrname .. ", addr = " .. addr)
end

s.start(...)