//
// Created by 文恒 on 2022/4/10.
//

#include "server.h"

#include <iostream>
#include <thread>
void server::run()
{
    socket_ptr p_socket(new ip::tcp::socket(m_ioserver));

    m_acceptor.async_accept(*p_socket, boost::bind(&server::handler_connect, this, boost::placeholders::_1, p_socket));


}

void server::handler_connect(const boost::system::error_code& ec, socket_ptr& p_socket)
{
    if(ec)
    {
        std::cerr << "server: connect error..." << std::endl;
        return;
    }

    std::cout << "ok..., client connect\tremote ip: " << p_socket->remote_endpoint().address().to_string() << std::endl;


    std::string msg("server connect successfully~~~, server ip: ");
    msg += p_socket->local_endpoint().address().to_string();
    p_socket->async_write_some(buffer(msg), boost::bind(&server::handler_write, this, boost::placeholders::_1, p_socket));

    p_socket->async_read_some(buffer(m_buf), boost::bind(&server::handler_read, this, boost::placeholders::_1, placeholders::bytes_transferred));

    run();
}

void server::handler_write(error_code_type ec, socket_ptr& p_socket)
{
    using namespace std;
    if(ec)
    {
         cerr << "handler error..." << endl;
         return;
    }

    auto p = [p_socket](){
        string send_buf;
        while(getline(cin, send_buf) && send_buf != "q")
        {
            cout << "server msg: " << send_buf << endl;

            p_socket->send(buffer(send_buf));
        }
    };

    thread t1(p);

    t1.detach();


}

void server::handler_read(error_code_type ec, size_t bytes)
{
    using namespace std;
    if(ec)
    {
        cerr << "handler read error..." << endl;
        return;
    }


    cout << "client msg: " << m_buf << "\t" << bytes << "bytes" << endl;
}