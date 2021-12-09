#!/bin/bash
#使用tee命令来将数据显示在STDOUT和文件上

tempfile=teeLogfile

echo "this is first line" | tee $tempfile
echo "this is second line" | tee -a $tempfile
echo "this is third line" | tee -a $tempfile

echo "show the $tempfile content:"
cat $tempfile