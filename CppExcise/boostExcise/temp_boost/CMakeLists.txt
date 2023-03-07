cmake_minimum_required(VERSION 3.21)
project(temp_boost)

set(CMAKE_CXX_STANDARD 14)

link_libraries(-lboost_filesystem -lboost_system)
add_executable(temp_boost
        main.cpp)
