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
        key = math.random(1, 999999),
        lost_conn_time = nil,
        msgcache = {}
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

local function process_reconnect(fd, msg)
    local playerid = tonumber(msg[2])
    local key = tonumber(msg[3])

    local conn = conns[fd]
    skynet.error("gateway svr: playerid = " .. playerid .. ", 尝试重登....")
    if not conn then
        skynet.error("gateway svr: 该连接非法...  fd = " .. fd)
        return
    end

    local gateplayer = players[playerid]
    if not gateplayer then
        skynet.error("gateway svr: 玩家未登录...")
        return
    end

    if gateplayer.conn then
        skynet.error("gateway svr: 该玩家仍在登录...")
        return
    end

    if gateplayer.key ~= key then
        skynet.error("gateway svr: 该玩家客户端无效重登...")
        return
    end

    gateplayer.conn = conn
    conn.playerid = playerid

    s.resp.send_by_fd(nil, fd, {"reconnect", 0})

    for i, cmsg in ipairs(gateplayer.msgcache) do
        s.resp.send_by_fd(nil, fd, cmsg)
    end

    gateplayer.msgcache = {}
end

local process_msg = function(fd, msg)
    local cmd, msgtb = str_unpack(msg)

    skynet.error("[ " .. fd .. " ]: process_msg --> " .. msg .. ", cmd = " .. cmd)

    -- skynet.error("process_msg -> " .. cmd)
    -- for k, v in ipairs(msgtb) do
    --     skynet.error("process_msg -> value = " .. v)
    -- end
    
    -- for k, v in pairs(svr_addr or {}) do
    --     skynet.error("k = " .. k .. ", v = " .. v)
    -- end

    local conn = conns[fd]
    local playerid = conn.playerid

    --重连特殊处理
    if cmd == "reconnect" then
        process_reconnect(fd, msgtb)
        return
    end


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
        skynet.error("gateway"..s.id.. ": cmd = " .. cmd .. ", agent = " .. (agent or -1))
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
    if not c then 
        return 
    end

    local playerid = c.playerid
    if not playerid then 
        return 
    else
        local gplayer = players[playerid]
        gplayer.conn = nil
        skynet.timeout(300 * 100, function()
            if gplayer.conn then return end

            skynet.error("gateway svr: 玩家长时间未重登，强制下线!!!")
            local reason = "断线"
            s.call(runconfig.agentmgr.node, "agentmgr", "reqkick", playerid, reason)
        end)
    end

    -- players[playerid] = nil
    -- local reason = "断线"
    -- skynet.error("gateway start to disconnect: playerid = " .. playerid)
    -- skynet.call(svr_addr["agentmgr"], "lua", "reqkick", playerid, reason)
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

    if s.close then
        skynet.error("gateway svr: node = " .. skynet.getenv("node") .. ", id = " .. s.id .. " --> close...")
        return
    end

    local c = conn()
    conns[fd] = c
    c.fd = fd

    skynet.fork(recv_loop, fd)
end

function s.init()
    skynet.error("[ " .. s.name .. " " .. s.id)
    s.close = false
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

    -- for k, v in pairs(msg) do
    --     skynet.error("send_by_fd --> k = " .. k .. ", v = " ..v)
    -- end

    local buff = str_pack(msg[1], msg)
    skynet.error("send " .. fd .. " --> [ " .. msg[1] .. " ] {" .. table.concat(msg, ",").. "}")
    socket.write(fd, buff)
end

s.resp.send = function(source, playerid, msg)
    local gplayer = players[playerid]
    if not gplayer then return end

    local c = gplayer.conn

    if not c then 
        table.insert(gplayer.msgcache, msg)
        if #gplayer.msgcache > 100 then
            s.call(runconfig.agentmgr.node, "agentmgr", "reqkick", playerid, "缓存消息过多")
        end
        return 
    end

    s.resp.send_by_fd(nil, c.fd, msg)
end

s.resp.sure_agent = function(source, fd, playerid, agent)
    local conn = conns[fd]
    if not conn then 
        skynet.call("agentmgr", "lua", "reqkick", playerid, "踢人下线")
        return false
    end

    conn.playerid = playerid
    local gplayer = gateplayer()
    gplayer.agent = agent
    gplayer.playerid = playerid
    gplayer.conn = conn
    players[playerid] = gplayer

    skynet.error("gateway: sure_agent call ok, playerid = " .. playerid .. ", agent = " .. agent .. ", key = " .. gplayer.key)

    return true
end

s.resp.kick = function(source, playerid)
    local gplayer = players[playerid]
    skynet.error("gateway resp kick: playerid = " .. playerid)
    if not gplayer then 
        return 
    end

    local c = gplayer.conn
    players[playerid] = nil

    if not c then 
        return 
    end
    conns[c.fd] = nil
    disconect(c.fd)

    socket.close(c.fd)
end

s.resp.shutdown = function ()
    skynet.error("gateway svr: node = " .. skynet.getenv("node") .. ", id = " .. s.id .. " --> shutdown")
    s.close = true
end


s.start(...)