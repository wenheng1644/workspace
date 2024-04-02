local skynet = require("skynet")
local s = require("service")

s.client = {}


s.resp.client = function(source, cmd, msg)
    s.gate = source
    local func = s.client[cmd]

    if not func then
        skynet.error("agent srv: not the cmd func --> " .. cmd)
        return
    end

    func(msg, source)
end

s.resp.kick = function(source)
    skynet.sleep(200)
end

s.resp.exit = function(source)
    skynet.exit()
end


s.init = function()
    skynet.sleep(200)

    s.data = {
        coin = 100,
        hp = 200,
    }
end


s.client.work = function(msg)
    s.data.coin = s.data.coin + 1

    return {"work", s.data.coin}
end

s.start(...)