cmake_minimum_required(VERSION 3.21)
project(DrawCardApp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(source)
include_directories(source/server)
include_directories(source/server/CardPool)
include_directories(source/server/drawCard)
include_directories(testClion_trunk)

add_executable(DrawCardApp
        source/server/CardPool/cardpool.cpp
        source/server/CardPool/cardpool.h
        source/server/drawCard/draw.cpp
        source/server/drawCard/draw.h
        source/server/drawCard/drawcard_Data.h
        testClion_trunk/main.cpp source/server/myLog/mylog.cpp source/server/myLog/mylog.h)
