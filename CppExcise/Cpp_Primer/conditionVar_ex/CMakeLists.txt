cmake_minimum_required(VERSION 3.23)
project(conditionVar_ex)

set(CMAKE_CXX_STANDARD 14)
link_libraries(pthread)
add_executable(conditionVar_ex
        main.cpp)
