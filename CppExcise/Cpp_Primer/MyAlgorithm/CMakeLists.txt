cmake_minimum_required(VERSION 3.22)
project(MyAlgorithm)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(MyAlgorithm
        main.cpp
        myAlgorithm.cpp
        myAlgorithm.h)
