cmake_minimum_required(VERSION 3.25)
project(newFrameEx)


set(CMAKE_CXX_STANDARD 17)

add_executable(newFrameEx main.cpp)

target_link_libraries(newFrameEx pthread boost_thread)