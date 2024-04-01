local skynet = require("skynet")
local s = require("service")

s.client = {}

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
    skynet.error("login recv " .. msg[1] .. " " .. msg[2])
    return {"login", -1, "test"}
end

s.start(...)