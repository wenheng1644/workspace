cmake_minimum_required(VERSION 3.26)
project(workthread)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)


add_executable(workthread main.cpp
        WorkThread.cpp
        WorkThread.h
        threadSafe_Container.h
        task.h
        task.cpp
        threadSafe_Container.cpp
        netMsg.h
        netMsg.cpp)

target_link_libraries(workthread pthread boost_thread)
