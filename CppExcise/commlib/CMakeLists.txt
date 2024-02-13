cmake_minimum_required(VERSION 3.25)
project(commlib)

set(CXX_STANDARD 17)

aux_source_directory(. MAIN_DIR)
# aux_source_directory(./cmdcomm CMDCOMM_DIR)
aux_source_directory(./cmdcomm/net CMDCOMM_NET_DIR)
aux_source_directory(./comm COMM_DIR)
aux_source_directory(./TCP_comm TCP_COMM_DIR)



add_library(commlib SHARED  ${MAIN_DIR} ${COMM_DIR} ${TCP_COMM_DIR} ${CMDCOMM_NET_DIR})