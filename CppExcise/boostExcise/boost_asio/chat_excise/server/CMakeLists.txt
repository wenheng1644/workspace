cmake_minimum_required(VERSION 3.21)
project(server)

set(CMAKE_CXX_STANDARD 14)
link_libraries(ws2_32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
include_directories(.)
include_directories("C:\\exlib\\boost\\include\\boost-1_78")

link_libraries("C:\\exlib\\boost\\lib")

link_libraries("libwsock32.a")
add_executable(server
        main.cpp
        server.cpp
        server.h
        chatMsg.h chatMsg.cpp)
