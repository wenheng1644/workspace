local skynet = require("skynet")
local s = require("service")
local mysql = require("skynet.db.mysql")
local runconfig = require("runconfig")

s.client = {}

local PLAYER_DATAS_TYPE = {
    INSERT = 1,
    UPDATE = 2,
    DEL = 3,
}

local addrs = {}

--处理玩家数据
local function onHandlePlayerDatas(agent, ontype)
    if not agent or not agent.db then return end

    local db = agent.db

    local sql = nil

    if ontype == PLAYER_DATAS_TYPE.INSERT then
        sql = string.format("insert into player_datas (account, coin, hp) values (\'%s\', \'%s\', \'%s\')", agent.id, agent.data.coin or 0, agent.data.hp or 200)
    elseif ontype == PLAYER_DATAS_TYPE.UPDATE then
        sql = string.format("update player_datas set coin = \'%s\', hp = \'%s\' where account = \'%s\'", agent.data.coin or 0, agent.data.hp or 200, agent.id)
    end

    if not sql then return end

    db:query(sql)

    skynet.error("agent svr: id = " .. agent.id .. " --> sql do success ( " .. sql .. " )")
end

s.resp.client = function(source, cmd, msg)
    s.gate = source
    local func = s.client[cmd]

    if not func then
        skynet.error("agent srv: not the cmd func --> " .. cmd)
        return
    end

    local ret = func(msg, source)
    skynet.send(source, "lua", "send", s.id, ret)
end

s.resp.kick = function(source)
    -- skynet.sleep(200)
    onHandlePlayerDatas(s, PLAYER_DATAS_TYPE.UPDATE)

end

s.resp.exit = function(source)
    onHandlePlayerDatas(s, PLAYER_DATAS_TYPE.UPDATE)

    skynet.exit()
end

s.resp.regist_addr = function(source, addrname, addr)
    addrs[addrname] = addr

    skynet.error("agent svr: regist ---> addrname = " .. addrname .. ", addr = " .. addr)
end


s.init = function()
    skynet.sleep(200)

    s.db = mysql.connect({
        host = "localhost",
        port = 3306,
        database = "game",
        user = "root",
        password = "123456",
        max_packet_size = 1024*1024,
        on_connect = nil
    })

    local sql = string.format("select * from player_datas where account = \'%s\'", s.id)
    local res = s.db:query(sql)

    if #res == 0 then
        s.data = {
            coin = 0,
            hp = 200,
        }

        onHandlePlayerDatas(s, PLAYER_DATAS_TYPE.INSERT)
        skynet.error("agent svr: s.id = " .. s.id .. ", 新用户使用默认数据")

        return
    end

    local data = res[1]
    s.data = {
        coin = data.coin,
        hp = data.hp
    }

    skynet.error("agent svr: s.id = " .. s.id .. ", 读取db数据成功!!")

end


s.client.work = function(msg)
    s.data.coin = s.data.coin + 1

    return {"work", s.data.coin}
end

s.client.quit = function(msg)
    -- skynet.send(addrs["agentmgr"], "lua", "reqkick", s.id, "玩家退出登录")
    s.send(runconfig.agentmgr.node, addrs["agentmgr"], "reqkick", s.id, "玩家退出登录")
    return {"quit ok"}
end

s.client.print = function(msg)

    skynet.error("agent svr: print cmd --> type(msg) = " .. type(msg) .. ", len = " .. #msg)

    for k, v in pairs(msg) do
        skynet.error("###################  k = " .. k .. ", v = " .. v)
    end


    local ret = {"print"}
    local str1 = string.format("coin = %s", s.data.coin or 0)
    local str2 = string.format("hp = %s", s.data.hp or 200)

    if #msg == 1 or msg[2] == "all" then
        ret[2] = str1
        ret[3] = str2
        return ret
    end

    if msg[2] == "coin" then
        ret[2] = str1 
    elseif msg[2] == "hp" then
        ret[2] = str2
    else
        ret[2] = "not your data: " .. msg[2]
    end


    return ret
end

s.start(...)