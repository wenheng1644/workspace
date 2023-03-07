#!/bin/bash

for v in {0..500}
do
	let res=v%7
	echo "res = $res"
	if [ $res -eq 0 ]
	then
		echo $v
	fi
done
