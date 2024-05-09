print("run lua init.lua")

function OnInit(id)
    print("[lua] main OnInit id: " .. id)

    local p1 = sunnet.NewService("chat")
    -- local p2 = sunnet.NewService("ping")

end

function OnExit()
    print("[lua] main OnExit")
end