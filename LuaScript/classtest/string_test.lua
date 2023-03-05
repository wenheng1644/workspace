
local str = "hello linux"
local str2 = string.gsub(str, "linux", "world")
print("str = ", str, "str2 = ", str2)

local str_cn = "你好，邝慧娴"
print(string.format("#str = %d\t#str_cn = %d\tlen(str_cn) = %d", #str, #str_cn, string.len(str_cn)))

local str_concat = 1 .. 2
print("str_concat = ", str_concat)

local str_longLine = [[
    hello world
    hello linux
    when can i work?
]]

print("str_longLine = ", str_longLine)

print("str add", "10" + 1)
print(tostring(10.0))

local str_obj = "hello my world"
local i, j = str_obj:find("world")
print("i = ",i , " j = ", j)

local str_ex1 = [==[
<![CDATA[
    hello world
]]>
]==]

local str_ex1_2 = "<![CDATA[\n  Hello world\n]]>"
print("ex1 = ", str_ex1)
print("ex1_2 = ", str_ex1_2)

local str_palin = "step on no pets"
print(str_palin == str_palin:reverse())

