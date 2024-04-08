local skynet = require("skynet")
local cjson =  require("cjson")
local pb = require "protobuf"

local function json_pack(msg)
    local body = cjson.encode(msg)

    local bodylen = string.len(body)
    local cmdlen = string.len(msg._cmd)
    local jsonlen = bodylen + 2


    local fmt = string.format("> i2 c%d", bodylen)
    local buff = string.pack(fmt, jsonlen, body)

    return buff
end

local function json_unpack(buff)
    local len = string.len(buff)
    local name_format = string.format("> i2 c%d", len - 2)

    local total, body = string.unpack(name_format, buff)
    print("total = " .. total)
    local isok, msg =  pcall(cjson.decode, body)
    
    if not isok then
        print("解析失败")
        return
    else
        print("解析成功 -> " .. msg._cmd)
    end

    return msg
end


function test1()
    local msg = {
        _cmd = "balllist",
        balls = {
            [1] = {id = 1, x = 1, y = 20, size = 1},
            [2] = {id = 2, x = 11, y = 25, size = 2},
        }
    }

    local buff = cjson.encode(msg)
    print(buff)
end

function test2()
    local buff = [[{"cmd" : "enter","playerid" : 101, "x" : 10, "y" : 20, "size" : 1}]]
    local isok, msg = pcall(cjson.decode, buff)
    if isok then
        print("msg.size = " .. msg.size .. ", cmd = " .. msg.cmd .. ", playerid = " .. msg.playerid)
    else
        print("err")
    end
end

function test3()
    local msg = {
        _cmd = "move",
        status = {
            [1] = {1, 220, 9},
            [2] = {1, 28, 8},
        }
    }

    local buff = json_pack(msg)
    print("打印json序列化buff: " .. buff .. ", len = " .. string.len(buff))

    json_unpack(buff)

end

function test4()
    pb.register_file("/home/wenheng/workspace/CppExcise/mySkynetPro/service/proto/login.pb")
    local msg = {
        id = 101,
        pw = 123456,
    }

    local buff = pb.encode("login.Login", msg)
    print("编码buff的len = " .. string.len(buff))

    local umsg = pb.decode("login.Login", buff)

    if not umsg then
        print("解码失败")
        return
    end

    print(string.format("id = %s, pw = %s", umsg.id, umsg.pw))
end


skynet.start(function()
    test4()
end)