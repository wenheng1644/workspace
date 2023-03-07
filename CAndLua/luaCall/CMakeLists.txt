cmake_minimum_required(VERSION 3.2)
project(luaCall)
set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/lua/include)
include_directories(.)
include_directories(/usr/local/include/boost)
include_directories(${PROJECT_SOURCE_DIR}/extra/cLua)
set(LIBPATH ${PROJECT_SOURCE_DIR}/extra/cLua/lib)

set(LIBRARY_OUTPUT_PATH ${LIBPATH})
set(LIBFILEPATH ${PROJECT_SOURCE_DIR}/extra/cLua)

file(GLOB_RECURSE INCLUDES ${LIBFILEPATH}/*.h)
file(GLOB SOURCES ${LIBFILEPATH}/*.cpp)


include_directories(${LIBPATH})
link_directories(${LIBPATH})
link_libraries(libmylib.so)

link_directories(/usr/local/lua/lib)
link_libraries(liblua.a)


aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
aux_source_directory(${PROJECT_SOURCE_DIR}/extra/cLua LIB_LIST)

#add_library(mylib SHARED ${INCLUDES} ${SOURCES})


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(luaCall ${SRC_LIST})
target_link_libraries(luaCall stdc++fs dl)
