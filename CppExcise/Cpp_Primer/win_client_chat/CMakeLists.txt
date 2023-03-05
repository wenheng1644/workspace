cmake_minimum_required(VERSION 3.23)
project(win_client_chat)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
link_libraries(ws2_32)

add_executable(win_client_chat
        main.cpp
        win_client_chat.cpp
        win_client_chat.h)
