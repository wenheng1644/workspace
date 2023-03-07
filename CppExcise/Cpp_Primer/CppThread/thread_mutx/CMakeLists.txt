cmake_minimum_required(VERSION 3.21)
project(thread_mutx)

set(CMAKE_CXX_STANDARD 14)

add_executable(thread_mutx
        ex_mutex.cpp)

find_package(Threads REQUIRED)
target_link_libraries(thread_mutx Threads::Threads)
