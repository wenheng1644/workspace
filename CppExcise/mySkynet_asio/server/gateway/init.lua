require("severStartConfig")

local g_sid
local g_fd_uuid
local Svr_TYPE = "gateway"
---@type gateConnList
local connList = {
    list = {},
}


local gateconn = require("gateuser")



local net_comm = require("net_comm")
local server_comm = require("servers_comm")
function OnInit(server_id, gateid)
    g_sid = server_id

    local conf = ServerConfig[Svr_TYPE]

    if not conf or not conf[gateid] then
        print(string.format("服务类型 = %s, id = %s, sid = %s 配置不存在....", Svr_TYPE, gateid, server_id))
        return
    end
    local gatewayConf = conf[gateid]

    print(string.format("服务初始化: Svr_TYPE = %s, sid = %s, port = %s", Svr_TYPE, server_id, gatewayConf.port or "nil"))
    net_comm.listen(server_id, gatewayConf.port, gatewayConf.ip)
end

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

function OnServerMsg(source, ...)
    print("接收到其他服务的数据： source = ", source)

    local args = {...}
    for k, v in ipairs(args) do
        print(string.format("额外参数[%s]  -----> type(v) = %s,  v = %s", k, type(v), tostring(v)))
        if type(v) == "table" then
            for k1, v1 in pairs(v) do
                print(string.format("table key = %s, 值 = %s", k1, v1))
            end
        end
    end
    print(string.format("OnServerMsg | gateway 接收到的数据数量 agrs count = %s", #args))
end

net_comm.register(NET_TYPE.ACCEPT, onAcceptMsg)
net_comm.register(NET_TYPE.DATA, onSocketRWMsg)
net_comm.register(NET_TYPE.CLOSE, onSocketClose)


