#!/bin/bash
#创建临时目录

tempdir=$(mktemp -d dir.XXXXXX)
echo "show the tempdir: $tempdir"
ls -l

cd $tempdir
tempfile1=$(mktemp file1.XXXXXX)
tempfile2=$(mktemp file2.XXXXXX)

exec 7>$tempfile1
exec 8>$tempfile2

echo "this is temp1" >&7
echo "this is temp2" >&8

echo "show now open filedicstp:"
lsof -a -p $$ -d 7,8

echo "ok...."