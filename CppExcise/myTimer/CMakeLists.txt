cmake_minimum_required(VERSION 3.23)
project(myTimer)

set(CMAKE_CXX_STANDARD 14)
link_libraries(pthread)
add_executable(myTimer
        main.cpp myTimer.cpp myTimer.h)
