
---@class serverData
---@field type          string
---@field sid           integer
---@field

---@class gateconn
---@field account   string      帐号
---@field password  string      密码
---@field sex       integer     性别
---@field conn_id   string      socket_uid
---@field serverDatas      table<integer, serverData>       关联的服务， 数组类型
---@field serverDatas_map   table<integer, integer>         key是服务id， 值是serverDatas索引

---@class gateConnList
---@field list      table<string, gateconn>


---@type gateconn
local gateconn = {
    account = "",
    password = "",
    sex = 0,
    conn_id = "",
    serverDatas = {},
    serverDatas_map = {}
}


---@return gateconn
function gateconn.new()
    local tb = {}

    setmetatable(tb, gateconn)

    return tb
end


return gateconn