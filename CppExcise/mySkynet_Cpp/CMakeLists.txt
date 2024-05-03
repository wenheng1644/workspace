project(sunnet)
cmake_minimum_required(VERSION 3.25)

include_directories(./include)
aux_source_directory(./src DIR_SRCS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BINARY_DIR ./build)

#link_directories(/usr/local/lib)
link_libraries(liblua.a)

add_executable(sunnet ${DIR_SRCS}
        include/Sunnet.h
        src/Sunnet.cpp
        src/main.cpp
        include/Worker.h
        src/Worker.cpp
        include/Msg.h
        include/Service.h
        src/Service.cpp
        include/SocketWorker.h
        src/SocketWorker.cpp
        include/Conn.h
        src/LuaAPI.cpp)

target_link_libraries(sunnet pthread)