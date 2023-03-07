#!/bin/bash

#测试case语法
echo "this is a case test"
if [ $# -ne 1 ];then
	echo "the arg must be one"
	exit
fi

case $1 in
"wenheng")
	echo "hello $1, welcome here";;
"root")
	echo "welcome, super user~~";;
*)
	echo "error user, system will be closed";;
esac

