-- local firend = require "firend"
print(package.path)
package.path = package.path .. ";D:\\MyGitHub\\workspace\\LuaScript\\classtest\\?.lua"
local str = package.path
print(str)

local firend = require("firend")

local f1 = firend:new()

f1:print()

local f2 = bestFirend:new()
print("f2 nice = ", f2.nice)
print("===============")
f2:print()

module()