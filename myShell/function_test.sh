#!/bin/bash

#函数测试脚本

function add()
{
	sum=$[$1 + $2]
	echo "$sum"
}

read -p "input first arg = " arg1
read -p "input second arg = " arg2

sum=$(add $arg1 $arg2)
echo "the sum is ${sum}"


