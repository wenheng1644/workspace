cmake_minimum_required(VERSION 3.24)
project(boost_asio_client)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
include_directories(.)

set(netResolverPath /home/wenheng/Desktop/workspace/CppExcise/boostExcise/boost_asio_new/netResolver)
include_directories(${netResolverPath})
include_directories(${netResolverPath}/lib)
link_directories(${netResolverPath}/lib)

find_package(Boost REQUIRED COMPONENTS serialization)


add_executable(boost_asio_client
        client.cpp
        client.h
        main.cpp
        ../boost_asio_new/cmd/base_cmd.cpp
        ../boost_asio_new/common/user.cpp)

target_link_libraries(boost_asio_client pthread NetResolver Boost::serialization)
