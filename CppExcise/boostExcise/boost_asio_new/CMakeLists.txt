cmake_minimum_required(VERSION 3.24)
project(boost_asio_new)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)

include_directories(network)
include_directories(/usr/local/include)

include_directories(netResolver)
include_directories(netResolver/lib)
link_directories(netResolver/lib)

include_directories(${PROJECT_SOURCE_DIR}/CScriptSystem)
link_directories(${PROJECT_SOURCE_DIR}/CScriptSystem/lib)
link_libraries(libcscriptsystem.so)

#include_directories(/home/wenheng/QtFolder/Qt/6.2.4/gcc_64/include)
include_directories(/home/wenheng/QtFolder/Qt/6.2.4/gcc_64/lib/cmake/Qt6)

#设置某些库的cmake路径
set(CMAKE_PREFIX_PATH /home/wenheng/QtFolder/Qt/6.2.4/gcc_64/lib/cmake)

#link_directories(/usr/local/lib)
#link_libraries(liblua.a)

set(CMAKE_TOOLCHAIN_FILE "~/.clion-vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

find_package(sol2 CONFIG REQUIRED)
include_directories(${sol2_INCLUDE_DIRS})
message("sol2_INCLUDE_DIRS = " ${sol2_INCLUDE_DIRS})

find_package(Boost REQUIRED COMPONENTS serialization)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(boost_asio_new
        network/network.cpp
        network/network.h
        main.cpp  chat/chatRoom.cpp chat/chatRoom.h logManager/logManager.cpp logManager/logManager.h common/commonClass.h common/commonClass.cpp cmd/base_cmd.h cmd/base_cmd.cpp common/user.cpp common/user.h cmd/playerSys_cmd.h cmd/playerChat_cmd.h
        cmd/factory.h
        netResolver/netQtResolver.cpp
        netResolver/netQtResolver.h)

#target_compile_options(boost_asio_new PRIVATE -fPIC)

target_link_libraries(boost_asio_new pthread NetResolver Boost::serialization)
target_link_libraries(boost_asio_new  sol2)
target_link_libraries(boost_asio_new stdc++fs)
target_link_libraries(boost_asio_new Qt${QT_VERSION_MAJOR}::Core)

#include(GNUInstallDirs)
#install(TARGETS boost_asio_new
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#)
