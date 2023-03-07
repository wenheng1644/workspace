#!/bin/bash

if [ "$1" = "wenheng"  -o  "$1" = "root" ];then
	echo "welcome $1"
else
	echo "invailable user"
fi

echo "now ${1}"
