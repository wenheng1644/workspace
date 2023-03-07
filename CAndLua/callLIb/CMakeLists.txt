cmake_minimum_required(VERSION 3.23)
project(callLIb)

set(CMAKE_CXX_STANDARD 17)
set(LIBPATH ${PROJECT_SOURCE_DIR}/../theLIb)
include_directories(${LIBPATH})
link_directories(${LIBPATH}/bin)

add_executable(callLIb main.cpp)
target_link_libraries(callLIb libtheLIb.so)
