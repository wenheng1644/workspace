cmake_minimum_required(VERSION 3.21)
project(server)

set(CMAKE_CXX_STANDARD 14)
link_libraries(ws2_32)
#第三方库头文件路径
include_directories(C:\\exlib\\boost\\include\\boost-1_78)
#第三方库文件路径
link_directories(C:\\exlib\\boost\\lib)
include_directories(.)

add_executable(server
        synserver.cpp)
target_link_libraries(server ${Boost_LIBRARIES})
