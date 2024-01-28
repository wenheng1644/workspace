cmake_minimum_required(VERSION 3.25)
project(newFrameEx)


set(CMAKE_CXX_STANDARD 17)

include_directories(./comm ./cmd ./cmd/chatcmd ./cmd/resolvecmd/) 

aux_source_directory(./comm COMM_CPPDIR)
aux_source_directory(./netcomm NETCOMM_CPPDIR)
aux_source_directory(./netcomm/chatcmd NETCOMM_CHATCMD_CPPDIR)
aux_source_directory(./netcomm/cmddispatch NETCOMM_CMDDISPATCH_CPPDIR)
aux_source_directory(./netcomm/net NETCOMM_NET_CPPDIR)
aux_source_directory(./server SERVER_CPPDIR)
aux_source_directory(. MAIN_CPPDIR)

add_executable(newFrameEx   ${COMM_CPPDIR}
                            ${NETCOMM_CPPDIR}
                            ${NETCOMM_CHATCMD_CPPDIR}
                            ${NETCOMM_CMDDISPATCH_CPPDIR}
                            ${NETCOMM_NET_CPPDIR}
                            ${SERVER_CPPDIR}
                            ${MAIN_CPPDIR})

# add_executable(newFrameEx main.cpp
#                             ./netcomm/netcmdfunc.cpp
#                             ./netcomm/net/netMsg.cpp
#                             ./netcomm/net/resolveManager.cpp
#                             ./netcomm/chatcmd/chatcmd.pb.cc
#                             ./netcomm/baseCmd/basecmd.pb.cc
#                             ./netcomm/cmddispatch/CallBack.cpp
#                             ./netcomm/cmddispatch/DisPatcher.cpp
#                             ./comm/singleton.h
#                             ./comm/singleton.cpp
#                             ./comm/resourceManager.cpp
#                             ./comm/WorkRunner.cpp
#                             ./comm/commhead.cpp
#                             ./server/TCPConnection.cpp
#                             ./server/TCPServer.cpp
#                             )

target_link_libraries(newFrameEx pthread boost_thread protobuf)
