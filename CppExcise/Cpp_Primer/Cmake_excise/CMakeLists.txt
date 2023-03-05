cmake_minimum_required(VERSION 3.10)

project(Cmake_excise)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_CXX_FLAGS "-pthread")
aux_source_directory(. SRC_LIST)

add_executable(Cmake_excise ${SRC_LIST})