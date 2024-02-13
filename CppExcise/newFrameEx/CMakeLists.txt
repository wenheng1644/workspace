cmake_minimum_required(VERSION 3.25)
project(newFrameEx)


set(CMAKE_CXX_STANDARD 17)

set(TCPCOMLIB_DIR /home/wenheng/workspace/CppExcise/commlib)

include_directories(./comm ./cmd ./cmd/chatcmd ./cmd/resolvecmd/) 
link_directories(/usr/local/lib)

include_directories(
                    ${TCPCOMLIB_DIR}/cmdcomm
                    ${TCPCOMLIB_DIR}/cmdcomm/net
                    ${TCPCOMLIB_DIR}/comm
                    ${TCPCOMLIB_DIR}/TCP_comm
                    )

link_directories((${TCPCOMLIB_DIR}/build))  #自定义TCP网络库


aux_source_directory(./comm COMM_CPPDIR)
aux_source_directory(./netcomm NETCOMM_CPPDIR)
aux_source_directory(./netcomm/chatcmd NETCOMM_CHATCMD_CPPDIR)
aux_source_directory(./netcomm/cmddispatch NETCOMM_CMDDISPATCH_CPPDIR)
aux_source_directory(./server SERVER_CPPDIR)
aux_source_directory(. MAIN_CPPDIR)
aux_source_directory(./logic LOGIC_CPPDIR)

add_executable(newFrameEx   ${COMM_CPPDIR}
                            ${NETCOMM_CPPDIR}
                            ${NETCOMM_CHATCMD_CPPDIR}
                            ${NETCOMM_CMDDISPATCH_CPPDIR}
                            ${SERVER_CPPDIR}
                            ${MAIN_CPPDIR}
                            ${LOGIC_CPPDIR})


target_link_libraries(newFrameEx pthread boost_thread protobuf commlib)
