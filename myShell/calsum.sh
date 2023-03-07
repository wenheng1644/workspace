#!/bin/bash

#累加脚本

if [ $# -ne 1 ];then
	echo "args need one"
	exit
fi

sum=0
for((i=1;i <= $1;i++ ));do
	sum=$[$sum + $i]
done

echo "the anwser is $sum"
