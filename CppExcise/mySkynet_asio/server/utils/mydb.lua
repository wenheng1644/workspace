--[[
    打包luadb模块
]]


local luasql = require("luasql.mysql")

local sql_env = luasql.mysql()
--assert(not sql_env, "sql_env error")

local sql_conn = sql_env:connect("skynet", "root", "xwz111598")


--assert(not sql_conn, "sql_conn error")

print("数据库连接成功!!!!")

local mydb = {}

function mydb.select(sql)
    local stmt, err = sql_conn:execute(sql)
    if not stmt then
        print("Error executing statement: ", err)
        sql_conn:close()
        os.exit(1)
    end

    local cnt = 0
    local ret = {}
    while true do
        local row, err = stmt:fetch({}, "a")
        if not row then
            break
        end
        cnt = cnt + 1

        ret[#ret + 1] = row
    end

    stmt:close()

    print(string.format("mydb.select | 查询sql = (%s) 数量 = %s", sql, cnt))

    return ret
end




return mydb