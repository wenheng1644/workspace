cmake_minimum_required(VERSION 3.21)
project(boostExcise)

set(CMAKE_CXX_STANDARD 14)

set(BOOST_LIBRARYDIR "C:\\exlib\\boost\\lib")
#link_libraries(ws2_32)

find_package(Boost 1.78.0 REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
#第三方库头文件路径
include_directories(C:\\exlib\\boost\\include\\boost-1_78)
#第三方库文件路径
link_directories(C:\\exlib\\boost\\lib)
link_directories(C:\\exlib\\boost\\lib\\cmake)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
aux_source_directory(. DIR_SRCS)

include_directories(${Boost_INCLUDE_DIRS})
set(Boost_USE_STATIC_LIBS ON)


add_executable(boostExcise
        main.cpp)
#target_link_libraries(boostExcise boost_thread-1.78.0 boost_system)
target_link_libraries(boostExcise ${Boost_LIBRARIES})
