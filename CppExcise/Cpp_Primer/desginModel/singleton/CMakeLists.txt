cmake_minimum_required(VERSION 3.23)
project(singleton)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(singleton
        singleton.cpp
        singleton.h main.cpp)
