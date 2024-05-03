print("run lua init.lua")

function OnInit(id)
    print("[lua] main OnInit id: " .. id)

    local p1 = sunnet.NewService("ping")
    local p2 = sunnet.NewService("ping")

    print(string.format("[lua] main svr open ping svr ---> p1 = %s, p2 = %s", p1, p2))

    local ret1, ret2 = sunnet.KillService(p1)

    print(string.format("KillService test --> p1 = %s, ret1 = %s, ret2 = %s", p1, ret1, ret2))
end

function OnExit()
    print("[lua] main OnExit")
end