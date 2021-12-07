#!/bin/bash
#阻止命令的输出,通过null文件实现
echo "show something"
ls -al > /dev/null
echo "display /dev/null"
cat /dev//null

echo "将testfile3数据清空"
cat /dev/null > testfile3
