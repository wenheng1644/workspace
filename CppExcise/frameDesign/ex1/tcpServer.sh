#!/bin/bash
MYPATH=./cmake-build-debug
IP=$1
PORT=$2

DEFALUT_IP=$(ifconfig | grep inet | grep -v inet6 | grep -v 127.0.0.1 | grep -v 0.0.0.0 | awk '{print $2}')
DEFALUT_PORT=8888

if [ ${IP} -z ] && [ ${PORT} -z ]; then
    IP=${DEFALUT_IP}
    PORT=${DEFALUT_PORT}

    echo "使用默认参数: DEFALUT_IP = ${DEFALUT_IP}, DEFALUT_PORT = ${DEFALUT_PORT}"
fi

echo "server info : ip=${IP}, port=${PORT}" 
./${MYPATH}/ex1 ${IP} ${PORT}