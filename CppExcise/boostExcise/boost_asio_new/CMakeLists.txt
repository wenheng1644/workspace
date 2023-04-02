cmake_minimum_required(VERSION 3.24)
project(boost_asio_new)

set(CMAKE_CXX_STANDARD 17)

include_directories(network)
include_directories(/usr/local/include)

add_executable(boost_asio_new
        network/network.cpp
        network/network.h
        main.cpp netResolver/netResolver.h netResolver/netResolver.cpp)

target_link_libraries(boost_asio_new pthread)
