cmake_minimum_required(VERSION 3.21)
project(chat_project)

set(CMAKE_CXX_STANDARD 14)

link_libraries(ws2_32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#第三方库头文件路径
include_directories(C:\\exlib\\boost\\include\\boost-1_78)
#第三方库文件路径
link_directories(C:\\exlib\\boost\\lib)

link_libraries("libwsock32.a")


include_directories(server)

add_executable(chat_project
        server/chatMsg.cpp
        server/chatMsg.h
        server/chatRoom.cpp
        server/chatRoom.h
        server/chatServer.cpp
        server/chatServer.h
        server/chatSession.cpp
        server/chatSession.h
        server/main.cpp)
