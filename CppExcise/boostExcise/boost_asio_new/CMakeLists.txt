cmake_minimum_required(VERSION 3.24)
project(boost_asio_new)

set(CMAKE_CXX_STANDARD 17)

include_directories(network)
include_directories(/usr/local/include)

include_directories(netResolver)
include_directories(netResolver/lib)
link_directories(netResolver/lib)

include_directories(${PROJECT_SOURCE_DIR}/CScriptSystem)
link_directories(${PROJECT_SOURCE_DIR}/CScriptSystem/lib)
link_libraries(libcscriptsystem.so)

set(CMAKE_TOOLCHAIN_FILE "~/.clion-vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

find_package(sol2 CONFIG REQUIRED)
include_directories(${sol2_INCLUDE_DIRS})
message("sol2_INCLUDE_DIRS = " ${sol2_INCLUDE_DIRS})

add_executable(boost_asio_new
        network/network.cpp
        network/network.h
        main.cpp  chat/chatRoom.cpp chat/chatRoom.h)

target_link_libraries(boost_asio_new pthread NetResolver)
target_link_libraries(boost_asio_new  sol2)
target_link_libraries(boost_asio_new stdc++fs)
