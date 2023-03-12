cmake_minimum_required(VERSION 3.24)
project(uptranslib)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(/usr/local/lua/include)
include_directories(.)
include_directories(/usr/local/include/boost)

link_directories(/usr/local/lua/lib)
link_libraries(liblua.a)

aux_source_directory(${PROJECT_SOURCE_DIR} SRC_LIST)

add_library(uptranslib SHARED ${SRC_LIST})
