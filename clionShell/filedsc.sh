#!/bin/bash

#测试lsof命令的使用

exec 3> testfile3
exec 6> testfile6
exec 7< testfile7

if [ ! -f "testfile7" ];then
  touch ./testfile7
fi
lsof -a -p $$ -d 0,1,2,3,6,7