cmake_minimum_required(VERSION 3.24)
project(callLib)

set(CMAKE_CXX_STANDARD 17)
set(LIBPATH D:\\MyGitHub\\workspace\\CppExcise\\Cpp_Primer\\theLib)
#link_libraries(-llibtheLib.dll)
include_directories(${LIBPATH})
link_directories(${LIBPATH}/lib)

add_executable(callLib main.cpp)

target_link_libraries(callLib libtheLib.dll)
