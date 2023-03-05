cmake_minimum_required(VERSION 3.23)
project(ex1)

include_directories(.)
include_directories(D:\\Lua\\5.4.3\\include)
#第三方库头文件路径
include_directories(C:\\exlib\\boost\\include\\boost-1_78)
link_directories(D:\\Lua\\5.4.3\\lib)

link_libraries(liblua.a)
link_directories(D:\\MyGitHub\\workspace\\CAndLua\\ex1\\lib)
link_libraries(libmylib.a)

set(CMAKE_CXX_STANDARD 17)
#set(LIBRARY_OUTPUT_PATH ..\\bin)

link_directories(${PROJECT_SOURCE_DIR}/lib)
link_libraries(libtestClass.dll)

aux_source_directory(${PROJECT_SOURCE_DIR} SRC)

add_executable(ex1
        ${SRC})
#target_link_libraries(ex1 libtestClass.dll)
#set(LIBRARY_OUTPUT_PATH "..//lib")
#add_library(mylib STATIC
#        cFunctionToLua.cpp cFunctionToLua.h)

#set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
#set(LIBFILE TestClass.h TestClass.cpp)
#add_library(testClass SHARED ${LIBFILE})


