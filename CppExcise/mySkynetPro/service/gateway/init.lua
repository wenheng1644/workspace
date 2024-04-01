local skynet = require("skynet")
local s = require("service")
local socket = require("skynet.socket")
local runconfig = require("runconfig")

conns = {}
players = {}

svr_addr = {}

function conn()
    local m = {
        fd = nil,
        playerid = nil,
    }

    return m
end

function gateplayer()
    local m = {
        playerid = nil,
        agent = nil,
        conn = nil,
    }

    return m
end

local str_unpack = function(msgstr)
    local msg = {}

    while true do
        local arg, reset = string.match(msgstr, "(.-),(.*)")
        if arg then
            table.insert(msg, arg)
            msgstr = reset
        else
            table.insert(msg, msgstr)
            break
        end
    end

    return msg[1], msg
end

local str_pack = function(cmd, msg)
    return table.concat(msg, ",") .. "\r\n"
end

local process_msg = function(fd, msg)
    skynet.error("[ " .. fd .. " ]: process_msg --> " .. msg)

    local cmd, msgtb = str_unpack(msg)

    skynet.error("process_msg -> " .. cmd)
    for k, v in ipairs(msgtb) do
        skynet.error("process_msg -> value = " .. v)
    end
    
    for k, v in pairs(svr_addr or {}) do
        skynet.error("k = " .. k .. ", v = " .. v)
    end

    local conn = conns[fd]
    local playerid = conn.playerid



    if not playerid then
        local node = skynet.getenv("node")
        local nodecfg = runconfig[node]
        local loginid = math.random(1, #nodecfg.login)

        local loginaddr = "login" .. loginid
        local login = svr_addr[loginaddr]
        skynet.error("start to login " .. loginaddr)
        skynet.send(login, "lua", "client", fd, cmd, msgtb)
        -- skynet.error("send login status = " .. status)
    else
        local gplayer = players[playerid]
        local agent = gplayer.agent

        skynet.send(agent, "lua", "client", cmd, msgtb)
    end
end

local  process_buff = function(fd, buff)
    while true do
        local msg, reset = string.match(buff, "(.-)\r\n(.*)")
        if msg then
            buff = reset
            process_msg(fd, msg)
        else
            return buff
        end
    end
end

local disconect = function(fd)
    local c = conns[fd]
    if not c then return end

    local playerid = c.playerid
    if not playerid then return end

    players[playerid] = nil
    local reason = "断线"
    skynet.call("agentmgr", "lua", "reqkick", playerid, reason)
end

local recv_loop = function(fd)
    socket.start(fd)
    skynet.error("socket connected " .. fd)

    local readbuff = ""

    while true do
        local recvstr = socket.read(fd)
        if recvstr then
            readbuff = readbuff .. recvstr
            readbuff = process_buff(fd, readbuff)
        else
            skynet.error("socket close " .. fd)
            disconect(fd)
            socket.close(fd)
            return
        end

    end
end

local connect = function(fd, addr)
    print("connect from " .. addr .. " " .. fd)
    local c = conn()
    conns[fd] = c
    c.fd = fd

    skynet.fork(recv_loop, fd)
end

function s.init()
    skynet.error("[ " .. s.name .. " " .. s.id)

    local node = skynet.getenv("node")
    local nodecfg = runconfig[node]
    local port = nodecfg.gateway[s.id].port

    local listenfd = socket.listen("0.0.0.0", port)

    skynet.error("Listen socket : ip = 0.0.0.0, port = " .. port )

    socket.start(listenfd, connect)

end

s.resp.regist_addr = function(source ,addrname, addr)
    skynet.error("[ " .. addrname .. " ]: " .. addr .. " register success!!!")
    svr_addr[addrname] = addr
end


s.resp.send_by_fd = function(source, fd, msg)
    if not conns[fd] then return end

    for k, v in pairs(msg) do
        skynet.error("send_by_fd --> k = " .. k .. ", v = " ..v)
    end

    local buff = str_pack(msg[1], msg)
    skynet.error("send " .. fd .. " --> [ " .. msg[1] .. " ] {" .. table.concat(msg, ",").. "}")
    socket.write(fd, buff)
end

s.resp.send = function(source, playerid, msg)
    local gplayer = players[playerid]
    if not gplayer then return end

    local c = gplayer.conn

    if not c then return end

    s.resp.send_by_fd(nil, c.fd, msg)
end

s.resp.sure_agent = function(source, fd, playerid, agent)
    local conn = conns[fd]
    if not conn then 
        skynet.call("agentmgr", "lua", "reqkick", playerid, "未完成登录即下线")
        return false
    end

    conn.playerid = playerid
    local gplayer = gateplayer()
    gplayer.agent = agent
    gplayer.playerid = playerid
    gplayer.conn = conn
    players[playerid] = gplayer

    return true
end

s.resp.kick = function(source, playerid)
    local gplayer = players[playerid]
    if not gplayer then return end

    local c = gplayer.conn
    players[playerid] = nil
    if not c then return end

    conns[c.fd] = nil
    disconect(c.fd)
    socket.close(c.fd)
end


s.start(...)