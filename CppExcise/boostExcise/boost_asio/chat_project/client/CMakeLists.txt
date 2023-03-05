cmake_minimum_required(VERSION 3.21)
project(client)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

link_libraries(ws2_32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#第三方库头文件路径
include_directories(C:\\exlib\\boost\\include\\boost-1_78)
#第三方库文件路径
link_directories(C:\\exlib\\boost\\lib)

link_libraries("libwsock32.a")

add_executable(client
        client.cpp
        client.h
        main.cpp)
