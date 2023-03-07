cmake_minimum_required(VERSION 3.21)
project(linux_thread)

set(CMAKE_CXX_STANDARD 14)

#target_link_libraries(-lptread)
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 -pthread")
add_executable(linux_thread
        main.cpp)
