local skynet = require("skynet")

skynet.start(function()

    local id = skynet.self()
    skynet.error("[ " .. id  .. " ]: " .. "start main scripy!!!")

    skynet.exit()

end)