cmake_minimum_required(VERSION 3.22)
project(thread_excise)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#第三方库头文件路径
include_directories(C:\\exlib\\boost\\include\\boost-1_78)
#第三方库文件路径
link_directories(C:\\exlib\\boost\\lib)

add_executable(thread_excise
        main.cpp
        task.cpp task.h)
