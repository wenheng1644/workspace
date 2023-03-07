#!/bin/bash

#测试read输入用法

read -t 7 -p "enter your name(7s): " name

if [ -z $name ]
then
	echo -e "\nno enter"
	exit
fi

echo "your name = ${name}"
