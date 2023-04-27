cmake_minimum_required(VERSION 3.26)
project(cscriptsystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=default")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")


set(CMAKE_TOOLCHAIN_FILE "~/.clion-vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
include_directories(/usr/local/include)

find_package(sol2 CONFIG REQUIRED)

link_directories(/usr/local/lib)
link_libraries(liblua.a)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
aux_source_directory(${PROJECT_SOURCE_DIR} SCR_LIST)

find_library(DL_LIBRARY dl)
link_libraries(sol2)
if(DL_LIBRARY)
    message("DL_LIBRARY: " ${DL_LIBRARY})
    link_libraries(${DL_LIBRARY})
endif()

add_library(cscriptsystem SHARED ${SCR_LIST})

