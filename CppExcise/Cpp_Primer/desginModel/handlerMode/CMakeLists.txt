cmake_minimum_required(VERSION 3.23)
project(handlerMode)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(handlerMode
        handler.cpp
        handler.h
        main.cpp)
