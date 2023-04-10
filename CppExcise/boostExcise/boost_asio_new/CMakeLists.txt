cmake_minimum_required(VERSION 3.24)
project(boost_asio_new)

set(CMAKE_CXX_STANDARD 17)

include_directories(network)
include_directories(/usr/local/include)

include_directories(netResolver)
include_directories(netResolver/lib)
link_directories(netResolver/lib)

add_executable(boost_asio_new
        network/network.cpp
        network/network.h
        main.cpp  chat/chatRoom.cpp chat/chatRoom.h)

target_link_libraries(boost_asio_new pthread NetResolver)
