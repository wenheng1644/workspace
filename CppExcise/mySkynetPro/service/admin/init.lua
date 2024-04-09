local skynet = require("skynet")
local socket = require("skynet.socket")
local s = require("service")
local runconfig = require("runconfig")

require("skynet.manager")

local function recv_loop(fd)
    socket.start(fd)
    socket.write(fd, "please enter a cmd: \r\n")

    while true do
        local cmd = socket.readline(fd, "\r\n")
        if not cmd then
            socket.close(fd)
            break
        end

        if cmd == "stop" then
            skynet.error("admin svr: 开始关闭网关!!!")
            stop()
        end

        skynet.error("admin svr: recv cmd = " .. cmd)
    end

    skynet.error("admin svr: close...")
end

local function connect(fd, addr)
    skynet.error("admin svr: connected fd = " .. fd .. ", addr = " .. addr)
    skynet.fork(recv_loop, fd)
end

s.init = function ()
    local listenfd =  socket.listen("127.0.0.1", 8888)
    socket.start(listenfd, connect)
end

s.resp.regist_addr = function(source, node ,addrname, addr)
    s.addrs = s.addrs or {}
    s.addrs[node] = s.addrs[node] or {}
    s.addrs[node][addrname] = addr

    skynet.error("@@@@@@@@@@@@@@@@@@@@@admin svr: id = " .. s.id .. ", node = " .. node ..", regist addrname = " .. addrname .. ", addr = " .. addr)
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