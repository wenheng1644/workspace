
local server_comm =  require("servers_comm")
local net_comm = require("net_comm")
require("severStartConfig")


function main()
    print("hello this is lua: main ok")

    for serverType, conf in pairs(ServerConfig) do
        for configid , v in pairs(conf) do
            local gateway = net_comm.NewService("gateway", configid)
            local ailsname = serverType .. configid
            server_comm.register(ailsname, gateway)

            print(string.format("启动服务类型: %s, ailsname = %s, configid = %s, svrid = %s",
                serverType, ailsname, configid, gateway))
        end
    end

    print("启动login服务")

    local login = sunnet.NewService("login", 1,2, "hhhh")
    server_comm.register("login", login)

end

main()