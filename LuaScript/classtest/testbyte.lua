local function readbyte(filename)
    local fd = io.open(filename, "rb")
    assert(fd, "file cant open")

    -- local blocksize = 16

    -- for bytes in fd:lines(blocksize) do
    --     print("orgin bytes: ", bytes)
    --     for i = 1, #bytes do
    --         local b = string.unpack("B", bytes, i)
    --         -- print(string.format("%02X", b))
    --         io.write(string.format("%02X ", b))
    --     end
    --     print(string.rep(" ", blocksize - #bytes))
    --     bytes = string.gsub(bytes, "%c", ".")
    --     print("bytes: ", bytes)
    -- end
    local str = fd:read("a")
    print(str)
end

readbyte("./classtest/testbyte.lua")
