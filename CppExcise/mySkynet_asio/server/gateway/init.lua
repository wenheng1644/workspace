require("severStartConfig")

local whmod = require("whmod")

local g_sid
local g_fd_uuid
local Svr_TYPE = "gateway"
---@type gateConnList
local connList = {
    list = {},
}


local gateconn = require("gateuser")

local function onAcceptMsg(fd_uuid)
    --g_fd_uuid = fd_uuid
    local gateconn = gateconn.new()
    gateconn.conn_id = fd_uuid
    connList.list[fd_uuid] = gateconn
    print("[lua]onAcceptMsg | 接收到客户端连接 ---> ", fd_uuid)
end

local function onSocketRWMsg(fd_uuid, data)
    print("[lua]onSocketRWMsg | 接收到网络数据: datas =", data, ", len = ", string.len(data), " from ", fd_uuid)
end

local function onSocketClose(fd_uuid)
    print(string.format("[lua]onSocketClose | 网络断开: fd_uuid = %s", fd_uuid or "nil"))

    local conn = connList.list[fd_uuid]
    if conn then
        if conn.serverDatas then
            for _, v in ipairs(conn.serverDatas) do
                --通知关闭
                v.close()
            end

        end
        connList.list[fd_uuid] = nil
    end


    --to-do 通知相关服务关闭
end

local SvrHandleFuncs = {}
SvrHandleFuncs.test = function(source, ...)
    local args = {...}
    print(string.format("test_command 来源服务 ---> source = %s, #args = %s", source, #args))

    for k, v in ipairs(args) do
        print(string.format("test_command ----> k = %s, v = %s", k, v))
    end
end

local function OnServerMsg(source, command, ...)
    local f = SvrHandleFuncs[command]

     if not f then
         print(string.format("whmod.registerSvrHandle | command = %s 事件未注册", command))
         return
     end
    f(source, ...)
end


local function OnInit(server_id, gateid, type_)
    g_sid = server_id

    local conf = ServerConfig[Svr_TYPE]

    if not conf or not conf[gateid] then
        print(string.format("服务类型 = %s, id = %s, sid = %s 配置不存在....", Svr_TYPE, gateid, server_id))
        return
    end
    local gatewayConf = conf[gateid]

    whmod.registerNet(ACCEPT, onAcceptMsg)
    whmod.registerNet(DATA, onSocketClose)
    whmod.registerNet(CLOSE, onSocketClose)

    whmod.registerSvrHandle(OnServerMsg)

    print(string.format("服务初始化: Svr_TYPE = %s, sid = %s, port = %s", Svr_TYPE, server_id, gatewayConf.port or "nil"))
    --net_comm.listen(server_id, gatewayConf.port, gatewayConf.ip)

    sunnet.Listen(server_id, gatewayConf.port, gatewayConf.ip)

end

whmod.start(OnInit, ...)


