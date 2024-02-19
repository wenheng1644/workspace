//
// Created by wenheng on 23年12月9日.
//

#include "TCP_Server.h"

TCP_Server::TCP_Server(TCP_Server::ioserver_type &io, TCP_Server::TCP::endpoint ed) :
    m_io(io), m_acceptor(m_io, ed)
{

}
