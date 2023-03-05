//
// Created by 文恒 on 2022/4/10.
//

#include "client.h"

#include <iostream>
#include <thread>


void client::run()
{
    m_socket.async_connect(ip::tcp::endpoint(ip::address::from_string("127.0.0.1"), 8001),
                           boost::bind(&client::handler_connect, this, placeholders::error));
}

void client::handler_connect(const error_code_type &ec)
{
    using namespace std;
    if(ec)
    {
        cerr << "client connect error..." << endl;
        return;
    }

    cout << "client connect successfully~~" << endl;

    string data;

    while(getline(std::cin, data))
    {
        write(data);
    }

}

void client::write(std::string &data)
{
    msgHeader header;
    header.bodySize = strlen(data.c_str());
    header.sysId = 1;
    header.pid = 1;

    char head[6] = {};
    memcpy(head, (void*)&header, sizeof(msgHeader));
    std::string strHead(head, sizeof(msgHeader));

    std::string pack = strHead + data;

//    m_socket.send(buffer(pack.c_str(), strlen(pack.c_str())));
    m_socket.write_some(buffer(pack.c_str(), strlen(pack.c_str())));
}
