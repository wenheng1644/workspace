//
// Created by 文恒 on 2022/4/3.
//

#include "asynServer_client.h"

#include <iostream>
#include <string>

void asynServer_client::start()
{
    ip::udp::socket msocket(m_ioserver, ip::udp::endpoint(ip::udp::v4(), 8000));

    char buf[100] = {};

    while(true)
    {
        ip::udp::endpoint ep;
        size_t bytes = msocket.receive_from(buffer(buf), ep);

        std::cout << "udp client'endpoint: " << ep.address().to_string() << std::endl;

        std::string msg(buf, bytes);
        msocket.send_to(buffer(msg), ep);
    }
}