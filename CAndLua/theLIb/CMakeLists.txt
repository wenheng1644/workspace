cmake_minimum_required(VERSION 3.23)
project(theLIb)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_library(theLIb SHARED library.cpp)
