cmake_minimum_required(VERSION 3.21)
project(netlib)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
link_directories(/home/wenheng/Desktop/workspace/CppExcise/Cpp_Primer/netlib/lib)
link_libraries(netServer)


add_executable(netlib
        main.cpp)
#target_link_libraries(netlib netServer)
