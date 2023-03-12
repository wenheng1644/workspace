cmake_minimum_required(VERSION 3.24)
project(transliterLib)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(/usr/local/lua/include)
include_directories(.)
include_directories(/usr/local/include/boost)

link_directories(/usr/local/lua/lib)
link_libraries(liblua.a)

add_library(translib SHARED transLib.cpp)
