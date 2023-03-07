#!/bin/bash

#while 循环测试

if [ $# -ne 1 ]
then
	echo "arg must be one"
	exit
fi

cnt=0
sum=0

while [ $cnt -le $1 ]
do
	let sum+=cnt
	let cnt++
done
echo "sum = ${sum}"
