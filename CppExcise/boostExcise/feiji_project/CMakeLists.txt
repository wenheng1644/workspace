cmake_minimum_required(VERSION 3.26)
project(feiji_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(net)
include_directories(/usr/local/include)


add_executable(feiji_project
        net/chat_cmd.h
        net/cmd.h
        net/netserver.cpp
        net/netserver.h
        main.cpp net/playerInfo_cmd.h logic/userObj.h logic/userObj.cpp net/netSession.cpp net/netSession.h logic/UserEng.cpp logic/UserEng.h)

target_link_libraries(feiji_project pthread)
