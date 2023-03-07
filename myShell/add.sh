#!/bin/bash

#加法脚本
echo "there are $# args"
if [ $# -ne 2 ]; then
	echo "args need 2"
	exit
else
	echo "sum = $[$1 + $2]"
fi
