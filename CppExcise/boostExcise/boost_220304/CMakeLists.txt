cmake_minimum_required(VERSION 3.21)
project(boost_220304)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(boost_220304 main.cpp)

target_link_libraries(boost_220304 boost_thread boost_system)