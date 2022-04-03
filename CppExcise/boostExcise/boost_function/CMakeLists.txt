cmake_minimum_required(VERSION 3.21)
project(boost_function)

set(CMAKE_CXX_STANDARD 14)

add_executable(boost_function main.cpp functionCAllBack.cpp functionCAllBack.h)
