local s = require("service")
local skynet = require("skynet")

require("comm")

s.skin = {}


local skinSys = "skin"

local function getplayerSkinDatas(player)
    if not player then return end

    local data = player.data.serize_datas or {}

    local skinDatas = data[skinSys] or {}

    return skinDatas
end

local function setplayerSkinDatas(player, datas)
    if not player then return end

    player.data.serize_datas[skinSys] = datas or {}
end


--当天是否首次登录
local function isSendSkin(player)
    local skinDatas = getplayerSkinDatas(player)

    if not skinDatas or not skinDatas.sendskin then return true end

    return false
end

s.skin.OnSkinLogin = function()
    local skinDatas = getplayerSkinDatas(s)
    if not skinDatas then return end

    if isSendSkin(s) then
        local txt = string.format("skin sys: 玩家(%s) 登录首送皮肤!!!", s.id)
        skynet.error(txt)

        skinDatas.sendskin = 1
        skinDatas.skinid = 1998
        setplayerSkinDatas(s, skinDatas)
    end
end

s.skin.print = function()
    local skinDatas = getplayerSkinDatas(s)
    if not skinDatas then return "not skin datas" end
    local dataStr = string.format("skin datas --> playerid = %s, sendskin = %d, skinid = %d", s.id, skinDatas.sendskin or 0, skinDatas.skinid or 0)
    local txt = string.format("打印玩家皮肤数据: %s",dataStr)
    skynet.error(txt)

    return dataStr
end