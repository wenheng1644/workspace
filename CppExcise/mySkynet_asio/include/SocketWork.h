//
// Created by 文恒 on 24-10-8.
//

#ifndef SOCKETWORK_H
#define SOCKETWORK_H

#pragma once
#include "boost/asio.hpp"

#include "Conn.h"
#include "NetData.h"

class SocketWork
{
public:
    void Init();
    void operator()();

    void run(std::shared_ptr<tcp::acceptor> ac, u_int32_t srvid);

private:
    //监听到新客户端连接
    void OnAccept(std::shared_ptr<Conn> conn, u_int32_t srvid, std::shared_ptr<tcp::acceptor> ac, boost::system::error_code ec);

};


#endif //SOCKETWORK_H
