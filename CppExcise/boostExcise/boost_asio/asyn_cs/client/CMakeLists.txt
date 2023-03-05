cmake_minimum_required(VERSION 3.21)
project(client)

set(CMAKE_CXX_STANDARD 14)

link_libraries(ws2_32)
include_directories("C:\\exlib\\boost\\include\\boost-1_78")

link_directories("C:\\exlib\\boost\\lib")

add_executable(client
        main.cpp)

target_link_libraries(client ${Boost_LIBRARIES})

