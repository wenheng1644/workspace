
local SvrComm = require("whmod.SvrComm")
require("severStartConfig")


function main()
    print("hello this is lua: main ok")

    for serverType, conf in pairs(ServerConfig) do
        for configid , v in pairs(conf) do
            local gateway = SvrComm.NewService("gateway", configid, "gateway")
            local ailsname = serverType .. configid
            SvrComm.register(ailsname, gateway)

            print(string.format("启动服务类型: %s, ailsname = %s, configid = %s, svrid = %s",
                serverType, ailsname, configid, gateway))
        end
    end

    local login = SvrComm.NewService("login", 1,2, "hhhh")
    SvrComm.register("login", login)

end

main()