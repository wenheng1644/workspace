#!/bin/bash

PROGRASS_NAME="ex1"

pid=$(pgrep -n ${PROGRASS_NAME})

echo "脚本运行中"

if [ ${pid} -z ]; then
    echo "查找${PROGRASS_NAME}pid失败"
    exit -1
fi

echo "查找${PROGRASS_NAME}的进程id = ${pid}"

kill -9 ${pid}
echo "${PROGRASS_NAME} 进程已杀死"