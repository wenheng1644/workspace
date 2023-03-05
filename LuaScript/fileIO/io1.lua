--测试lua文件IO

local function readLineByfile(filename)

    -- local file = io.open(filename,"r")

    -- io.input(file)
    for line in io.lines(filename) do
        print("current line: ",line)
    end 

end

local function readFileByTotalMode(filename)

    local file = io.open(filename,"r")

    local totalBytes = file:seek("end")
    local bytes = file:seek("end",-25)

    print("totalBytes: ",totalBytes)
    print("bytes: ",bytes)

    print(file:read("*a"))

    file:close()
end

readFileByTotalMode("test.txt")

