cmake_minimum_required(VERSION 3.23)
project(templateMode)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(templateMode
        templateMode.cpp
        templateMode.h
        main.cpp)
