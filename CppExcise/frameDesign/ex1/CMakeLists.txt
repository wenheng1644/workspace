cmake_minimum_required(VERSION 3.26)
project(ex1)

set(CMAKE_CXX_STANDARD 17)
set(mysqlConnPath /home/wenheng/Desktop/workspace/CppExcise/mysqlEx)
include_directories(/usr/local/include)

include_directories(/home/wenheng/QtFolder/Qt/6.2.4/gcc_64/include)
include_directories(/home/wenheng/QtFolder/Qt/6.2.4/gcc_64/lib/cmake/Qt6)

include_directories(${mysqlConnPath})
link_directories(${mysqlConnPath}/lib)
link_libraries(libmysqlconn.so)

#设置某些库的cmake路径
set(CMAKE_PREFIX_PATH /home/wenheng/QtFolder/Qt/6.2.4/gcc_64/lib/cmake)

find_package(Boost REQUIRED COMPONENTS headers)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Boost REQUIRED COMPONENTS log log_setup)


add_executable(ex1 main.cpp
        common/threadSafe_Container.cpp
        common/threadSafe_Container.h
        TCP_Server/TCP_Server.cpp
        TCP_Server/TCP_Server.h
        TCP_Server/Session.cpp
        TCP_Server/Session.h
        common/task.cpp
        common/task.h
        common/CSourceEng.cpp
        common/CSourceEng.h
        netResolver/base_cmd.h
        netResolver/base_cmd.cpp
        netResolver/netQtResolver.h
        netResolver/netMsg.h
        netResolver/netMsg.cpp
        netResolver/user_cmd.cpp
        netResolver/sys_cmd.cpp
        netResolver/sys_cmd.h
        common/timer.h
        common/timer.cpp
        logManager/logManager.h
        logManager/logManager.cpp
        logManager/logManager.h
        logManager/logManager.h
        common/comm_func.cpp
        common/comm_func.h
        logic/user.cpp
        logic/user.h
        common/MysqlHandler.cpp
        common/MysqlHandler.h
        logic/chatRecordManager.cpp
        logic/chatRecordManager.h)

target_link_libraries(ex1 Boost::headers Threads::Threads OpenSSL::Crypto OpenSSL::SSL)
target_compile_definitions(ex1 PRIVATE BOOST_MYSQL_SEPARATE_COMPILATION)
target_link_libraries(ex1 pthread boost_thread)
target_link_libraries(ex1 stdc++fs)
target_link_libraries(ex1 Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(ex1 Boost::log)
target_link_libraries(ex1 ${Boost_LIBRARIES})

#target_link_libraries(ex1 mysqlconn)
