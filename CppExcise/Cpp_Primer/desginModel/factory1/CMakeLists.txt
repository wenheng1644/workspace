cmake_minimum_required(VERSION 3.23)
project(factory1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(factory1
        factoryOp.cpp
        factoryOp.h
        Operator.cpp
        Operator.h main.cpp)
