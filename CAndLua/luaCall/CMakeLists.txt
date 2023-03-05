cmake_minimum_required(VERSION 3.2)
project(luaCall)
include_directories(D:\\Lua\\5.4.3\\include)
include_directories(.)
include_directories(C:\\exlib\\boost\\include\\boost-1_78)
include_directories(${PROJECT_SOURCE_DIR}/extra/cLua)
set(LIBPATH ${PROJECT_SOURCE_DIR}/extra/cLua/lib)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARY_OUTPUT_PATH ${LIBPATH})
set(LIBFILEPATH ${PROJECT_SOURCE_DIR}/extra/cLua)

#set(CMAKE_C_COMPILER C:/Compiler/mingw64/bin/gcc.exe)
#set(CMAKE_CXX_COMPILER C:/Compiler/mingw64/bin/g++.exe)

file(GLOB_RECURSE INCLUDES ${LIBFILEPATH}/*.h)
file(GLOB SOURCES ${LIBFILEPATH}/*.cpp)

include_directories(${LIBPATH})
link_directories(${LIBPATH})
link_libraries(libcFunlib.a)

link_directories(D:\\Lua\\5.4.3\\lib)
link_libraries(liblua.a)




aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)
#
aux_source_directory(${PROJECT_SOURCE_DIR}/extra/cLua LIB_LIST)
#set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)
#
#add_library(cFunlib STATIC ${INCLUDES} ${SOURCES})
#install(TARGETS cFunlib LIBRARY DESTINATION lib)
#install(FILES ${LIBFILEPATH}/luaCall.h ${LIBFILEPATH}/cFunctionToLua.h DESTINATION include)
#
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(luaCall ${SRC_LIST})
#include_directories(${LIBFILEPATH})
#link_libraries(${LIBFILEPATH})
#
#target_link_libraries(luaCall ${LIBPATH}/libcFunlib.dll)
#target_link_libraries(luaCall ${LIBPATH}/libcFunlib.dll.a)

#