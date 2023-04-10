cmake_minimum_required(VERSION 3.24)
project(libNetResolver)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
aux_source_directory(${PROJECT_SOURCE_DIR} SRC_LIST)

add_library(NetResolver SHARED ${SRC_LIST} ../netMsg/netMsg.h)