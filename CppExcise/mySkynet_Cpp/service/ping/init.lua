local serviceid


function OnInit(id)
    print("[lua] ping svr is running.... id = " .. id)
    serviceid = tonumber(id) or -1
end

function OnExit()
    print("[lua] ping svr is done....")
end

function OnServiceMsg(source, buff)
    print(string.format("[lua] OnServiceMsg: source = %s, buff = %s", source, buff))

    if(string.len(buff) > 10) then
        print("buff len to big: " .. string.len(buff))
        local ret1, ret2 = sunnet.KillService(serviceid)
        return
    end

    sunnet.Send(serviceid, source, buff .. "i")
end