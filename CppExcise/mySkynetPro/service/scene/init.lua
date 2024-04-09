local skynet = require("skynet")
local s = require("service")

local balls = {}

local MAX_X = 100
local MAX_Y = 100


function ball()
    local m = {
        playerid = nil,
        agent = nil,
        node = nil,

        x = math.random(0,100),
        y = math.random(0,100),

        size = 1,

        speedx = 0,
        speedy = 0,
    }

    return m
end

--场景所有球的协议消息
local function balllist_msg()
    local ret = {"balllist"}

    for _, data in pairs(balls) do
        table.insert(ret, data.playerid)
        table.insert(ret, data.x)
        table.insert(ret, data.y)
        table.insert(ret, data.size)
    end

    return ret
end



local foods = {}
local food_maxid = 0
local food_count = 0

function food()
    local m = {
        id = nil,
        x = math.random(0, 100),
        y = math.random(0, 100),
    }

    return m
end


--场景下所有食物位置协议
local function foodlist_msg()
    local ret = {"foodlist"}

    for _, data in pairs(foods) do
        table.insert(ret, data.id)
        table.insert(ret, data.x)
        table.insert(ret, data.y)
    end


    return ret
end

local function broadcast(msg)
    for _, obj in pairs(balls) do
        s.send(obj.node, obj.agent, "send", msg)
    end
end

s.resp.enter = function(source, playerid, agent, node)
    skynet.error("scene svr: node = " .. skynet.getenv("node") .. ", id = " .. s.id .. ", playerid = " .. playerid .. " 进行请求进入场景")
    if balls[playerid] then
        skynet.error("scene svr: playerid = " .. playerid .. " was gaming~~")
        return false
    end

    local data = ball()
    data.playerid = playerid
    data.agent = agent
    data.node = node

    local enter_msg = {"enter", playerid, data.x, data.y}
    broadcast(enter_msg)

    balls[playerid] = data
    local ret_msg = {"enter", 0, "成功进入游戏"}
    s.send(node, agent, "send", ret_msg)

    s.send(node, agent, "send", balllist_msg())

    s.send(node, agent, "send", foodlist_msg())

    skynet.error("scene svr: sid = " .. s.id .. ", playerid = " .. playerid .. ", agent = " .. agent .. ", node = " .. node .. "进入场景")
    return true
end

s.resp.leave = function(source, playerid)
    if not balls[playerid] then return false end

    skynet.error("#### scene svr: id = " .. s.id .. ", playerid = " .. playerid .. " leave the scene svr~~")
    balls[playerid] = nil

    local ret = {"leave", playerid}

    broadcast(ret)
end

s.resp.shift = function(source, playerid, x, y)
    local b = balls[playerid]
    if not b then return false end

    skynet.error("#### scene svr: id = " .. s.id .. ", rev msg --> playerid = " .. playerid .. ", x = " .. x .. "type(x) = " .. type(x)  .. ", y = " .. y .. ", type(y) = " .. type(y))
    b.speedx = tonumber(x) or 0
    b.speedy = tonumber(y) or 0
end

function move_update()
    for _, b in pairs(balls) do
        b.x = b.x + b.speedx * 0.2
        b.y = b.y + b.speedy * 0.2

        if b.x >= MAX_X then
            b.x = MAX_X
            b.speedx = 0
        end

        if b.y >= MAX_Y then
            b.y = MAX_Y
            b.speedy = 0
        end
        if b.speedx ~= 0 or b.speedy ~= 0 then
            skynet.error("scene svr: id = " .. s.id .. ", playerid = " .. b.playerid .. ", speedx = " .. b.speedx ..", type(b.speedx) = " .. type(b.speedx) .. ", speedy = " .. b.speedy .. ", type(b.speedy) = " ..type(b.speedy))
            if b.speedx ~= 0 then skynet.error("scene svr: id = " .. s.id .. " --> yes  b.speedx ~= 0 " .. b.speedx) end
            if b.speedy ~= 0 then skynet.error("scene svr: id = " .. s.id .. " --> yes  b.speedy ~= 0 " .. b.speedy) end
            local msg = {"move", b.playerid, b.x,  b.y}
            broadcast(msg)
        end
    end
end

function food_update()
    if food_count > 50 then
        return
    end

    if math.random(1,  100 ) < 50 then return end
    food_maxid = food_maxid + 1
    food_count = food_count + 1

    local f = food()
    f.id = food_maxid
    foods[f.id] = f

    -- skynet.error("scene svr: create a new food, sid = " .. s.id, ", fid = " .. f.id .. ", food_count = " .. food_count .. ", (" .. f.x .. ", " .. f.y .. ")")

    local msg = {"addfood", f.id, f.x, f.y}

    broadcast(msg)
end


function eat_update()
    for pid, b in pairs(balls) do
        for fid, f in pairs(foods) do
            if (b.x -  f.x)^2 +(b.y - f.y)^2 < b.size^2 then
                food_count = food_count - 1
                b.size = b.size + 1
                local msg = {"eat", b.playerid, fid, b.size}
                broadcast(msg)

                foods[fid] = nil
            end
        end
    end
end

function update(frame)
    food_update()
    move_update()
    eat_update()
end

s.init = function()
    skynet.fork(function()
        local stime = skynet.now()
        local frame = 0

        skynet.error("scene svr: 场景服事件循环.... sid = " .. s.id)
        while true do
            frame = frame + 1
            local isok, err = pcall(update, frame)

            if not isok then
                skynet.error(err)
            end


            local etime = skynet.now()
            local waittime = frame * 20 - (etime - stime)

            if waittime <= 0 then
                waittime = 2
            end

            skynet.sleep(waittime)
        end
    end)
end

s.start(...)