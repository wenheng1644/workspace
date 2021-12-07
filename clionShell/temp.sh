#!/bin/bash
#创建临时文件


tempfile=$(mktemp testtemp.XXXXXX)
exec 3>$tempfile

echo "this script write something to $tempfile"

echo "this is first line" >&3
echo "this is second line" >&3
echo "this is thrid line" >&3

exec 3>&-

echo "script is done...,show the content:"
cat $tempfile

rm -f $tempfile &> /dev/null

echo "now use -t option:"
tempfile2=$(mktemp -t temp2.XXXXXX)

echo "temp: first line" > $tempfile2
echo "temp: second line" >> $tempfile2

echo "show the $tempfile2 content:"
cat $tempfile2

rm -f $tempfile2