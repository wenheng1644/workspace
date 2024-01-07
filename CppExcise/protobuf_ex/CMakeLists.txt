cmake_minimum_required(VERSION 3.25)
project(protobuf_ex)

set(CMAKE_CXX_STANDARD 17)

add_executable(protobuf_ex main.cpp protomsg.pb.cc
        comm/CallBack.cpp
        comm/CallBack.h
        comm/DisPatcher.cpp
        comm/DisPatcher.h)
target_link_libraries(protobuf_ex pthread protobuf)
