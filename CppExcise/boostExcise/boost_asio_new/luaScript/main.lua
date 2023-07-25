---
--- Generated by EmmyLua(https://github.com/EmmyLua)
--- Created by wenheng.
--- DateTime: 23-4-24 上午12:17
---
package.path = package.path .. ";/home/wenheng/Desktop/workspace/CppExcise/boostExcise/boost_asio_new/luaScript/userglobal.lua"

require("userglobal")

function main()
    local date = os.date("*t")
    local datetime = string.format("%04d-%02d-%02d %02d:%02d:%02d", date.year, date.month, date.day, date.hour, date.min, date.sec)
    print(string.format("%s>main load: %s<%s", string.rep("-", 20), datetime, string.rep("-", 20)))

end

main()


function lua_writeFile(netMsg)
    if not netMsg then 
        print("netMsg is empty")
        return 
    end
    local head = netMsg.head
    --print(string.format("name = %s, ip = %s", head.info.name, head.info.ip))
    --print("netMsg's body = ", netMsg.body)
    local tb = {}
    tb.ip = head.info.ip
    tb.name = head.info.name
    tb.type = head.type
    tb.len = head.len
    tb.version = head.version
    tb.checknum = head.checknum
    tb.body = netMsg.body

    local str = string.serialize(tb)
    --print("序列化字符串: ", str)

    local _, date, datetime = GetDate()
    --print("date, datetime = ", date, datetime)
    --print("filepath = ", LOGFILEPATH .. date .. ".log")
    local fd = OpenFile(LOGFILEPATH .. CHATLOGFILENAME, "a+")
    local content = fd:read("*a")
    --print("content = ", content)

    local str2tb = string.unserialize(content)
    --print("type(str2tb) = ", type(str2tb))
    str2tb[datetime] = tb

    --dump(str2tb)

    fd:close()

    --print("打印序列化后的表： ", string.serialize(str2tb))
    fd = OpenFile(LOGFILEPATH .. CHATLOGFILENAME, "w")
    fd:write(string.serialize(str2tb))
    fd:close()
    print("fd wirte done")
end

function test_getuserdata(netPtr)
    print("type(netPtr) = ", type(netPtr))
    print(string.format("type = %d, len = %d, version = %d, checknum = %d", netPtr.type, netPtr.len, netPtr.version
        , netPtr.checknum))

    print("type(netPtr.info) = ", type(netPtr.info))
    print(netPtr.info.name, netPtr.info.ip)
end

function lua_loadNetMsg()
    print("lua_loadNetMsg | 开始加载聊天数据....")
    local tb = {}
    local _, date, datetime = GetDate()
    local fd = OpenFile(LOGFILEPATH .. CHATLOGFILENAME, "a+")
    local content = fd:read("*a")
    --print("lua_loadNetMsg | 打印數據111")
    --print(string.format("lua_loadNetMsg | content = %s", content))
    tb = string.unserialize(content)
    --print("lua_loadNetMsg | 打印數據222")
    --dump(tb)
    local array = {}
    -- for _, v in pairs(tb) do
    --     array[#array+1] = v
    -- end

    for datetime_str, info in pairs(tb) do
        info.times = GetTimeZoneFromDateTimeStr(datetime_str) or 0
        info.dateTime = datetime_str
        array[#array+1] = info
    end

    local sortFunc = function (t1, t2)
        if t1.times < t2.times then
            return true
        else
            return false
        end
    end
    table.sort(array, sortFunc)
    print("lua_loadNetMsg | 聊天数据加載完成")
    return array
end

--[[
    @function:  lua_writeDatasToFile
    @param:     netMsgs(聊天消息记录)

    @desc:      将聊天数据批量写入文件
    @return:    true/false(判断是否正确处理)
]]
function lua_writeDatasToFile(netMsgs)
    if not netMsgs or type(netMsgs) ~="table" then
        print("lua_writeDatasToFile | netMsgs not vaild " .. type(netMsgs))
        return false
    end

    local _, date, datetime_str = GetDate()
    local fd = OpenFile(LOGFILEPATH .. CHATLOGFILENAME, "a+")
    if not fd then 
        print("fd open error") 
        return false
    end
    local content = fd:read("*a")
    local str2tb = string.unserialize(content)

    -- local datas = {}
    --dump(netMsgs)
    local cnt = 0
    for index, tb in ipairs(netMsgs) do
        --local tb = {}
        --local head = msg.head
        --tb.ip = head.info.ip
        --tb.name = head.info.name
        --tb.type = head.type
        --tb.len = head.len
        --tb.version = head.version
        --tb.checknum = head.checknum
        --tb.body = msg.body

        --print(string.format("lua |index = %d, times = %d", index, tb.times))
        local _, _, datetime = GetDate(tb.times)
        str2tb[datetime or "nil"] = tb
        cnt = cnt + 1
        -- print(string.format("lua_writeDatasToFile | [%d]: content = %s & times = %d", cnt, tb.chatInfo.content or "nil", tb.times))
        -- print(string.format("[%d]: 序列化当前表: ", cnt))
        -- dump(tb)
        -- print("================================================================")
    end
    -- print(string.format("当前写入数据数量 = %d", cnt))
    --  print("打印序列化后的表：")
    --  dump(str2tb)

    fd:close()

    fd = OpenFile(LOGFILEPATH .. CHATLOGFILENAME, "w")
    fd:write(string.serialize(str2tb))
    fd:close()

    print(string.format("(%s): lua | log文件写入完毕", datetime_str))
    return true
end

--[[
    @function:  lua_loadMsg

    @desc:      打印当前内存聊天记录
]]
function lua_loadMsg()
    local room = getRoom()
    if not room then
        return
    end

    local msgs = room.msgs
    if not msgs then 
        return 
    end

    for index, msg in pairs(msgs) do
        local head = msg.head
        local body = msg.body

        local name  = head.info.name or ""
        local ip    = head.info.ip or ""
        local time  = head.info.times or 0

        local _, _, datetiem_str = GetDateTimeStrFromTimeZone(time)

        print(string.format("(%d)[time = %s, name = %s, ip = %s]: %s", index, datetiem_str or "nil", name, ip, body))
    end
    print("打印内存聊天记录完成~")
end

function GM_File(filename, needtip)
    print("args = ", filename, needtip)
    filename = filename or "./test_create.txt"

    if createFile then
        print("createFile func is here")
        if createFile(filename) then
            print("create file successfully")
        else
            print("create file error")
        end
    else
        print("createFile is not ...")
    end
end

function lua_loadSession()
    if not getRoom then
        print("lua |  not getRoom function")
        return
    end

    local room = getRoom()

    if not room then
        print("room obj is nil")
        return
    end

    --print(string.format("type(room.sessions) = %s", type(room.sessions)))
    if not room.sessions then
        print("room.sessions is nil")
        return
    end

    local sessions = room.sessions

    if #sessions == 0 then
        print("没有客户端连接...")
        return
    end

    local index = 0
    for _, session in pairs(sessions) do
        local name = session.name or "null"
        local ip = session:ip() or "error ip"
        local port = session:port() or -1
        print(string.format("%d: name = %s, ip = %s, port = %d",
                index + 1, name, ip, port))
        index = index + 1
    end
    print(string.format("lua_loadSession | 现在剩余连接数: %d", index))
end

function IsSessionExist(name)
    local room = getRoom()
    if not room then return end

    local seesions = room.sessions
    --if #seesions == 0 then
    --    print("没有客户端连接...")
    --    return
    --end

    for _, session in pairs(seesions or {}) do
        if name == (session.name or "") then
            return session
        end
    end
end

function lua_closeSession(name, msg)
    if type(name) ~= "string" then
        print("请输入要断开的客户端连接名字")
        return
    end

    print("lua_closeSession | ", name)
    local session = isSessionExist(name)
    if not session then
        print(string.format("没有找到指定客户端: %s", name))
        return
    end

    print("lua_closeSession | is exist")

    local room = getRoom()
    if not room then return end

    local goodbye = netMsg.new("server", "sys", "您已被系统踢了")
    session:deliver(goodbye)
    if session:close() then
        print(string.format("指定客户端(%s)关闭成功", name))
        local content = msg or string.format("sys 已将用户[%s]踢出去, 请各位引以为戒", name)
        local netMsg = netMsg.new("server", "sys", content)
        print("lua_closeSession | type(netMsg) = ", type(netMsg))
        room:deliver(netMsg, false)
        if room:leave(session) then
            print(string.format("%s 已移除出聊天室", name))
        end
        return
    end

    print("关闭失败....")
end

--直接在聊天室发消息
function lua_sysMsg(msg)
    local room = getRoom()
    if not room then return end

    local netMsg = netMsg.new("server", "sys", msg or "null")
    room:deliver(netMsg, false)
end

--对某个用户发消息
function lua_sendMsgToUser(name, msg)
    if type(name) ~= "string" then return end
    local session = isSessionExist(name)
    if not session then
        print(string.format("name = %s 不存在"))
        return
    end

    msg = msg or "系统信息"

    local netMsg = netMsg.new("服务端", "系统消息", msg)

    session:deliver(netMsg)
end

local banUserTb = {
    ["bbb"] = true,
    --["xwz1"] = true,
}

function IsBanUserTb(name)
    if type(name) ~= "string"  then return false end

    if not banUserTb[name] then return false end
    print(string.format("name = %s 禁止進入", name))
    return true
end

function SendMsgToUser(session, msg)
    if not session then return end

    local netMsg = netMsg.new("server", "sys", "您已进入黑名单")

    session:deliver(netMsg)
    --session:close()
end