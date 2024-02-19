cmake_minimum_required(VERSION 3.26)
project(IO_ex)

include_directories(/usr/local/include)


set(CMAKE_CXX_STANDARD 17)

add_executable(IO_ex main.cpp
        net/TCP_Server.cpp
        net/TCP_Server.h
        net/TCP_Connection.cpp
        net/TCP_Connection.h)
target_link_libraries(IO_ex pthread boost_thread)
target_link_libraries(IO_ex stdc++fs)