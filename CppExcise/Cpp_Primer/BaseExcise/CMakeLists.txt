cmake_minimum_required(VERSION 3.22)
project(BaseExcise)

set(CMAKE_CXX_STANDARD 14)
link_libraries(ws2_32)
add_executable(BaseExcise
        main.cpp
        myWinSock.cpp
        win_ChatExcise.cpp win_ChatExcise.h)
