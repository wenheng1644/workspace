cmake_minimum_required(VERSION 3.24)
project(theLib)

set(CMAKE_CXX_STANDARD 17)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
add_library(theLib SHARED library.cpp)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)
install(TARGETS theLib LIBRARY DESTINATION lib)
install(FILES ${PROJECT_SOURCE_DIR}/library.h  DESTINATION include)