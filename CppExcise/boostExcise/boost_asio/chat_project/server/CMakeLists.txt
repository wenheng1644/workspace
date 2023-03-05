cmake_minimum_required(VERSION 3.21)
project(server)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

link_libraries(ws2_32 libwsock32.a)
set(CMAKE_CXX_FLAGS "-pthread")

#第三方库头文件路径
include_directories(C:\\exlib\\boost\\include\\boost-1_78)
#第三方库文件路径
link_directories(C:\\exlib\\boost\\lib)

add_executable(server
        chatMsg.cpp
        chatMsg.h
        chatRoom.cpp
        chatRoom.h
        chatServer.cpp
        chatServer.h
        chatSession.cpp
        chatSession.h
        main.cpp dateTimeMgr.cpp dateTimeMgr.h)
