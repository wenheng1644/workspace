cmake_minimum_required(VERSION 3.24)
project(boost_asio_client)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
include_directories(.)

add_executable(boost_asio_client
        client.cpp
        client.h
        main.cpp
        ../boost_asio_new/netResolver/netResolver.h
        ../boost_asio_new/netResolver/netResolver.cpp)

target_link_libraries(boost_asio_client pthread)
