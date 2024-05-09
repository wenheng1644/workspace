local svrid
local conns = {}

function OnInit(id)
    print(string.format("[lua] chat svr init!!!  ---> %s", id or "nil"))
    svrid = tonumber(id) or -1
    sunnet.Listen(8001, id)
end

function OnExit()
    print(string.format( "[lua] chat svr close...  ---> %s", svrid or -1))
end

function OnAcceptMsg(listenfd, clientfd)
    print(string.format("[lua] OnAcceptMsg: listenfd = %s, clientfd = %s", listenfd, clientfd))
    conns[clientfd] = true
end


function OnSocketData(fd, buff)
    print(string.format("[lua] OnSocketData: fd = %s, buff = %s", fd, buff))

    for tofd in pairs(conns) do
        sunnet.Write(tofd, buff)
    end
end

function OnSocketClose(fd)
    print(string.format("[lua] OnSocketClose: fd = %s", fd))
    conns[fd] = nil
end