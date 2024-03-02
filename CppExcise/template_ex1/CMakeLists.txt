cmake_minimum_required(VERSION 3.25)
project(template_ex1)

set(CMAKE_CXX_STANDARD 17)

add_executable(template_ex1 main.cpp
        noneClassTemplate.h
        mulArgTemplate.h)
