cmake_minimum_required(VERSION 3.23)
project(Adpter)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Adpter
        Adpter.cpp
        Adpter.h main.cpp)
