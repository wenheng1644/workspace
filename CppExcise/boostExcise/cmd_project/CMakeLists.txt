cmake_minimum_required(VERSION 3.26)
project(cmd_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(/usr/local/include)

include_directories(/home/wenheng/QtFolder/Qt/6.2.4/gcc_64/include)
include_directories(/home/wenheng/QtFolder/Qt/6.2.4/gcc_64/lib/cmake/Qt6)

#设置某些库的cmake路径
set(CMAKE_PREFIX_PATH /home/wenheng/QtFolder/Qt/6.2.4/gcc_64/lib/cmake)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(cmd_project main.cpp
        cmd/base_cmd.h
        cmd/base_cmd.cpp
        cmd/user_cmd.cpp
        cmd/user_cmd.h
        cmd/netQtResolver.h
        threadPool/threadPool.cpp
        threadPool/threadPool.h
        threadPool/netMsgTask.cpp
        threadPool/netMsgTask.h)

target_link_libraries(cmd_project pthread)
target_link_libraries(cmd_project stdc++fs)
target_link_libraries(cmd_project Qt${QT_VERSION_MAJOR}::Core)