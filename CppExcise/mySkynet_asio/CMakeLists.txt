cmake_minimum_required(VERSION 3.29)
project(mySkynet_asio)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BOOSTPATH /opt/homebrew/Cellar/boost/1.86.0_2)

include_directories(./include)
include_directories(./include/net)
include_directories(/opt/homebrew/Cellar/lua/5.4.7/include/lua)
include_directories(/usr/local/include)

aux_source_directory(./src DIR_SRCS)
aux_source_directory(./src/net DIR_SRCS_NET)


find_package(Boost 1.86.0 REQUIRED COMPONENTS json)

include_directories(${BOOSTPATH}/include)
link_directories(${BOOSTPATH}/lib)
link_directories(/opt/homebrew/Cellar/lua/5.4.7/lib)

set(CMAKE_BINARY_DIR ./build)


link_libraries(liblua.a)

add_executable(mySkynet_asio ${DIR_SRCS} ${DIR_SRCS_NET}
        include/Msg.h
        include/Service.h
)

target_link_libraries(mySkynet_asio pthread Boost::json)