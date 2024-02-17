cmake_minimum_required(VERSION 3.25)

project(newFrame_gateway)
set(CXX_STANDARD 17)

set(TCPCOMLIB_DIR /home/wenheng/workspace/CppExcise/commlib)

include_directories(
                    ${TCPCOMLIB_DIR}/cmdcomm
                    ${TCPCOMLIB_DIR}/cmdcomm/net
                    ${TCPCOMLIB_DIR}/comm
                    ${TCPCOMLIB_DIR}/TCP_comm
                    )

link_directories((${TCPCOMLIB_DIR}/build))  #自定义TCP网络库
link_directories(/usr/local/lib)


aux_source_directory(. MAIN_DIR)
aux_source_directory(./comm COMM_DIR)
aux_source_directory(./TCP_gateway TCP_GATEWAY)
aux_source_directory(./logic LOGIC_DIR)

add_executable(newFrame_gateway ${MAIN_DIR}
                                ${COMM_DIR}
                                ${TCP_GATEWAY}
                                ${LOGIC_DIR})

target_link_libraries(newFrame_gateway  protobuf commlib)

target_link_libraries(newFrame_gateway pthread boost_thread)
