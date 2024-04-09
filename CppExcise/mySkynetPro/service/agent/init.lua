local skynet = require("skynet")
local s = require "service"
local mysql = require("skynet.db.mysql")
local runconfig = require("runconfig")
require "scene"

require("comm")
require("skin")

-- local str = string.format("################################################### agent s addr  = %s", s)
-- skynet.error(str)

-- s.client = {}
local PLAYER_DATAS_TYPE = {
    INSERT = 1,
    UPDATE = 2,
    DEL = 3,
}

s.addrs = {}
--处理玩家数据
local function onHandlePlayerDatas(agent, ontype)
    if not agent or not agent.db then return end

    local db = agent.db

    local sql = nil

    if ontype == PLAYER_DATAS_TYPE.INSERT then
        sql = string.format("insert into player_datas (account, coin, hp, datas) values (\'%s\', \'%s\', \'%s\', \'%s\')", agent.id, agent.data.coin or 0, agent.data.hp or 200, ToBinSerlizeDatas(agent.data.serize_datas) or "")
    elseif ontype == PLAYER_DATAS_TYPE.UPDATE then
        sql = string.format("update player_datas set coin = \'%s\', hp = \'%s\', datas = \'%s\' where account = \'%s\'", agent.data.coin or 0, agent.data.hp or 200, ToBinSerlizeDatas(agent.data.serize_datas) or "",agent.id)
    end

    if not sql then return end

    local status = db:query(sql)

    sql = string.format("update player set last_login = \'%s\' where account = \'%s\'", ToMysqlTime(agent.data.last_login or 0), agent.id)
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
    s.leave_scene()
    onHandlePlayerDatas(s, PLAYER_DATAS_TYPE.UPDATE)

end

s.resp.exit = function(source)
    onHandlePlayerDatas(s, PLAYER_DATAS_TYPE.UPDATE)

    skynet.exit()
end

s.resp.regist_addr = function(source, addrname, addr)
    s.addrs[addrname] = addr

    skynet.error("agent svr: regist ---> addrname = " .. addrname .. ", addr = " .. (addr or "nil"))
end

s.resp.send = function(source, msg)
    s.send(skynet.getenv("node") ,s.gate, "send", s.id, msg)
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

    local metatb = {}

    if #res == 0 then

        local datas = {}
        setmetatable(datas, metatb)
        s.data = {
            coin = 0,
            hp = 200,
            sex = "male",
            last_login = os.time(),
            serize_datas  = datas,
        }

        s.skin.OnSkinLogin()    --首次送皮肤
        onHandlePlayerDatas(s, PLAYER_DATAS_TYPE.INSERT)
        skynet.error("agent svr: s.id = " .. s.id .. ", 新用户使用默认数据")

        return
    end

    local data = res[1]
    local datas = UnSerlizeDatas(data.datas or "") or {}
    setmetatable(datas, metatb)
    s.data = {
        coin = data.coin,
        hp = data.hp,
        sex = data.sex,
        serize_datas =  datas,
        last_login = os.time()
    }

    s.skin.OnSkinLogin()
    skynet.error("agent svr: s.id = " .. s.id .. ", 读取db数据成功!!")

end


s.client.work = function(msg)
    s.data.coin = s.data.coin + 1

    local str = string.format("agent svr: print the agent table addr  = %s", s)
    skynet.error(str)
    return {"work", s.data.coin}
end

s.client.quit = function(msg)
    s.send(runconfig.agentmgr.node, "agentmgr", "reqkick", s.id, "玩家退出登录")
    -- s.send(runconfig.agentmgr.node, s.addrs["agentmgr"], "reqkick", s.id, "玩家退出登录")
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
    elseif msg[2] == "skin" then
        ret[2] = s.skin.print()
    else
        ret[2] = "not your data: " .. msg[2]
    end


    return ret
end


-- s.client.enter = agent_enter

s.start(...)

-- skynet.error("################################agent服务########################")
-- for k, v in pairs(s.client or {}) do
--     skynet.error("$$$$$$$$$$$$$$$$$$$$$$  k = " .. k)
-- end