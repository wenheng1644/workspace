local cjson = require("cjson")

function ToMysqlTime(time)
    local sql_time = os.date("%Y-%m-%d %H:%M:%S", time)
    return sql_time
end

function ToLuaTime(sql_time)
    if not sql_time then return 0 end
    local year,month, day, hour, min, sec = string.match(sql_time, "(.+)-(.+)-(.) (.+):(.+):(.+)")
    local tb = {
        year = year,
        month = month,
        day = day,
        hour = hour,
        min = min,
        sec = sec
    }

    local time = os.time(tb)

    return time
end

function ToBinSerlizeDatas(data)
    local buff = cjson.encode(data)

    local fmt = string.format("c%d", string.len(buff))
    local binary_datas = string.pack(fmt, buff)

    print(string.format("buff-len = %d, binary_datas-len = %d", string.len(buff), string.len(binary_datas)))
    return binary_datas
end

function UnSerlizeDatas(binary_datas)
    local len = string.len(binary_datas)
    if len <= 0 then return {} end

    local fmt = string.format("c%d", len)

    local serilze_datas = string.unpack(fmt, binary_datas)

    local datas = cjson.decode(serilze_datas)

    return datas
end