cmake_minimum_required(VERSION 3.23)
project(obverser)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(obverser
        subject.cpp
        subject.h comp1.cpp comp1.h comp2.cpp comp2.h main.cpp)
