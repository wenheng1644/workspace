cmake_minimum_required(VERSION 3.26)
project(log_ex)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "-g -Wall -DBOOST_LOG_DYN_LINK")


include_directories(/usr/local/include)

find_package(Boost REQUIRED COMPONENTS log log_setup)

add_executable(log_ex
        main.cpp
        logManager/logManager.cpp
        logManager/logManager.h)

target_link_libraries(log_ex ${Boost_LIBRARIES})
target_link_libraries(log_ex stdc++fs)
target_link_libraries(log_ex Boost::log)



