
local function time1()
    local timeTamp = os.time()

    print("the timeTamp = ", timeTamp)

    local curDate = os.date("*t")
    print(string.format("year = %d, month = %d, day = %d, hour = %d, min = %d, sec = %d, wday = %d",
        curDate.year, curDate.month, curDate.day, curDate.hour, curDate.min, curDate.sec, curDate.wday))

    print(os.date("今天是 %c"))
    print("无参数调用os.date() = ", os.date())
end

-- time1()

local function time2()
    local x = os.clock()
    local curDate = os.date("*t")
    print(string.format("cur date = %s", os.date("%c", os.time(curDate))))
    curDate.day = curDate.day - 40
    print("before 40 days = ", os.date("%c", os.time(curDate)))

    print("eslap time = ", os.clock() -x, os.difftime(os.clock(), x))
end

-- time2()

local function curDayTimes()
    local epoch = os.date("*t")
    epoch.hour = 0
    epoch.min = 0
    epoch.sec = 0

    local timeStamp = os.difftime(os.time(), os.time(epoch))
    print("timestamp = ", timeStamp)

    local min = 60
    local hour = 60 * min

    print(string.format("have done hour = %d, min = %d, sec = %d", timeStamp // hour, (timeStamp % hour) // min, timeStamp % 60))
end

-- curDayTimes()

local function getdYear(year)
    local t = {year = year,month = 1}

    local FEBTable = {year = year, month = 2, day = 1}
    FEBTable.day = FEBTable.day - 1
    local beforeDay = os.date("*t", os.time(FEBTable))
    local days = beforeDay.day

    for i = 1, days do
        t.day = i
        local curDate = os.date("*t", os.time(t))

        if curDate and curDate.wday == 6 then
            print(string.format("date = %s and yday = %d",os.date("%Y-%m-%d", os.time(curDate)), curDate.yday))
        end
    end

end

getdYear(2018)

local function testadd()
    local date = os.date("*t")
    date.day = date.day + 1
    print(os.date("%c", os.time(date)))
    date.month = date.month + 1
    print(os.date("%c", os.time(date)))

end

testadd()