local skynet = require("skynet")
local s = require("service")
local mysql = require("skynet.db.mysql")

s.client = {}

local addrs = {}

s.resp.client = function(source, fd, cmd, msg)
    skynet.error("s.resp.client is start " .. fd .. ", " .. cmd)
    if not s.client[cmd] then
        skynet.error("s.resp.client fail... " .. cmd)
        return
    end

    local ret_msg = s.client[cmd](fd, msg, source)
    skynet.send(source, "lua", "send_by_fd", fd, ret_msg)

end

s.client.login = function(fd, msg, source)
    skynet.error("login recv " .. msg[1] .. ", id = " .. msg[2] .. ", pw = " .. msg[3])

    local id = tonumber(msg[2])
    local pw = msg[3]

    local node = skynet.getenv("node")
    local sql = string.format("select * from player where account = \'%s\'", msg[2])
    local res = s.db:query(sql)
    -- if msg[2] == "759490883" and pw == "123" then
    --     skynet.error("the id success~~~")

    --     local status, agent = s.call(node, addrs["agentmgr"], "reqlogin", id, node, source)
    --     skynet.error("loginsvr : type(status) = " .. type(status) .. ", type(agent) = " .. type(agent))
        
    --     skynet.send(source, "lua", "sure_agent", fd, id, agent)

    --     return {"login", 0, "success"}
    -- end
    skynet.error("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$")
    for k, v in pairs(res or {}) do
        skynet.error("###############   v.account = " .. v.account .. ", v.password = " .. v.password)
    end
    -- skynet.error("print the res type = " .. type(res) .. ", account = " ..res.account .. ", pw = " .. res.password)
    if not res[1] then
        skynet.error("loginsvr: not the account....")
        local sql = string.format("insert into player (account, password) values (\'%s\', \'%s\')", msg[2], pw)
        s.db:query(sql)
        skynet.error("loginsvr: create the account ---> " .. msg[2])
        -- skynet.error("loginsvr: the db query status type = " .. type(status))
        -- for k, v in pairs(status) do
        --     skynet.error("###############" .. "k = " .. k .. ", v = " .. v)
        -- end
        -- return {"login", -1, "not account"}
    elseif pw ~= res[1].password then
        skynet.error("loginsvr: password is not ture")
        return {"login", -1, "worng password"}
    end

    skynet.error("the id success~~~")

    local status, agent = s.call(node, addrs["agentmgr"], "reqlogin", id, node, source)
    skynet.error("loginsvr : type(status) = " .. type(status) .. ", type(agent) = " .. type(agent))
    
    skynet.send(source, "lua", "sure_agent", fd, id, agent)
    return {"login", 0, "success"}
end

s.resp.regist_addr = function(source, addrname, addr, node)
    addrs[addrname] = addr
end

s.init = function()

    skynet.error("login svr start to connect db")
    s.db = mysql.connect({
        host = "localhost",
        port = 3306,
        database = "game",
        user = "root",
        password = "123456",
        max_packet_size = 1024*1024,
        on_connect = nil
    })
end

s.start(...)