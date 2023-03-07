cmake_minimum_required(VERSION 3.23)
project(testVector)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
link_directories(myVector.cpp)
add_executable(testVector
        myVector.cpp
        myVector.h main.cpp

        )
