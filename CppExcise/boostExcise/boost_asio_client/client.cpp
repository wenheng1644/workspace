//
// Created by wenheng on 23-3-26.
//

#include "client.h"

#include "iostream"

std::mutex client::s_mutex;

void client::connect()
{
    m_socket.async_connect(m_ed, [&](boost::system::error_code ec){
        if(!ec)
        {
            auto addr = m_socket.remote_endpoint().address();
            std::cout << "pre server addr = " << addr.to_string() << std::endl;

            std::thread t1(std::bind(&client::handle_write, this));
            handle_read();
            t1.detach();
//            m_socket.async_read_some(boost::asio::buffer(m_buf), [&](boost::system::error_code ec, size_t len)
//            {
//               if(!ec)
//               {
//                    std::cout << boost::format("read data(%d) = %s") % len << m_buf << std::endl;
//                    m_socket.async_write_some(boost::asio::buffer(m_buf, len), [&](boost::system::error_code ec, size_t len)
//                    {
//                       if(!ec)
//                       {
//                           std::cout << "echo data to server" << std::endl;
//                       }
//                    });
//
//                    memset(m_buf, 0, sizeof(m_buf)); //清空數據
//               }
//            });
        }
    });
}

void client::handle_read()
{
    char buff[1024] = {0};
    using namespace boost::system;
    m_socket.async_read_some(boost::asio::buffer(buff), [&](error_code ec, size_t len)
    {
        if(len == 0 || ec)
        {
            std::cerr << "Server error...." << std::endl;
            m_socket.close();
            exit(0);
        }

        if(!ec)
        {
            netHead head;
            std::shared_ptr<netMsg> msg = netResolver::generator()->resolver(buff, len);
            if(msg)
            {
                std::lock_guard<std::mutex> l(s_mutex);
//                std::cout << boost::format("read data(%d): %s") %(len - sizeof(netHead)) % body << std::endl;
            }
            handle_read(); //递归回调一下
        }
    });

}

void client::handle_write()
{
    std::string line;
    std::cout << "enter your data: ";
    while(std::getline(std::cin, line) && line != "quit")
    {

        if(!m_socket.is_open())
        {
            std::cout << "write data break" << std::endl;
            exit(0);
        }
        netHead head;
        head.len = strlen(line.c_str());
        head.type =  1;
        head.version = 1;
        auto buff =  netResolver::generator()->compose(head, line.data(), strlen(line.c_str()));
        m_socket.write_some(boost::asio::buffer(buff.get(), sizeof(head) + strlen(line.c_str())));

        {
            std::lock_guard<std::mutex> l(s_mutex);
            std::cout << "enter your data: ";
        }
    }
    m_socket.close();
    std::cout << "done!" << std::endl;

}
