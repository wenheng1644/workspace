cmake_minimum_required(VERSION 3.23)
project(memnto)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(memnto
        memnto.cpp
        memnto.h gameRole.cpp gameRole.h main.cpp)
