local skynet = require("skynet")
local socket = require("skynet.socket")
local s = require("service")
local runconfig = require("runconfig")
local mysql = require("skynet.db.mysql")

require("skynet.manager")

local function str_pack(msg)
    local buff = "(" .. msg[1] .. ")"

    local str
    if #msg > 1 then
        table.remove(msg, 1)
        str = "{ " .. table.concat(msg, ",") .. " }"
    end

    if str then
        buff = buff .. " --> " .. str
    end

    return buff

end

local function recv_loop(fd)
    socket.start(fd)
    socket.write(fd, "please enter a cmd: \r\n")

    while true do
        local cmd = socket.readline(fd, "\r\n")
        if not cmd then
            socket.close(fd)
            break
        end

        local func = s.client[cmd]
        if func then
            local res = func()
            socket.write(fd, str_pack(res))
        else
            skynet.error("admin svr: not cmd func = " .. cmd)
        end
        -- if cmd == "stop" then
        --     skynet.error("admin svr: 开始关闭网关!!!")
        --     stop()
        -- end

        skynet.error("admin svr: recv cmd = " .. cmd)
    end

    skynet.error("admin svr: close...")
end

local function connect(fd, addr)
    skynet.error("admin svr: connected fd = " .. fd .. ", addr = " .. addr)
    skynet.fork(recv_loop, fd)
end

s.init = function ()
    s.db = mysql.connect({
        host = "localhost",
        port = 3306,
        database = "game",
        user = "root",
        password = "123456",
        max_packet_size = 1024*1024,
        on_connect = nil
    })


    local listenfd =  socket.listen("127.0.0.1", 8888)
    socket.start(listenfd, connect)
end

s.resp.regist_addr = function(source, node ,addrname, addr)
    s.addrs = s.addrs or {}
    s.addrs[node] = s.addrs[node] or {}
    s.addrs[node][addrname] = addr

    skynet.error("@@@@@@@@@@@@@@@@@@@@@admin svr: id = " .. s.id .. ", node = " .. node ..", regist addrname = " .. addrname .. ", addr = " .. addr)
end

s.client.stop = function()
    skynet.error("admin svr: 开始关闭网关!!!")
    stop()

    return {"stop"}
end

s.client.getcnt = function()
    local sql = string.format("select count(*) as count from player")
    local res = s.db:query(sql)

    local onlinecnt = s.call(runconfig.agentmgr.node, "agentmgr", "onlinecnt")

    for k, v in pairs(res) do
        for k1, v1 in pairs(v) do
            skynet.error("k1 = " .. k1 .. ", v1 = " .. v1)

        end
    end

    local str = string.format("online num = %s, total num = %s", onlinecnt, res[1].count or -1)
    return {"getcnt", str}
end

s.client.dailylogin = function()
    local date_str = os.date("%Y-%m-%d")

    local sql = string.format("select * from player where last_login >= \'%s\'", date_str)
    skynet.error("admin svr: do sql " .. sql)

    local res = s.db:query(sql)

    local tb = {"dailylogin"}
    for k, v in pairs(res) do
        local str = ""
        for k1, v1 in pairs(v) do
            str = str .. k1 .. " : " .. v1 .. " "
        end
        table.insert(tb, str)
    end
    
    return tb
end

s.start(...)

local function shutdown_gate()
    for node in pairs(runconfig.cluster) do
        local nodecfg = runconfig[node]

        for k, v in pairs(nodecfg.gateway) do
            local name = "gateway" .. k

            s.call(node, s.addrs[node][name], "shutdown")
        end
    end
end

local function shutdown_agent()
    local anode = runconfig.agentmgr.node

    while true do
        local online_num = s.call(anode, "agentmgr", "shutdown", 3)

        if online_num <= 0 then break end

        skynet.sleep(100)
    end
end

function stop()
    shutdown_gate()
    shutdown_agent()

    -- skynet.abort()

    return "ok"
end