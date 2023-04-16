//
// Created by wenheng on 23-3-26.
//

#include "client.h"

#include "iostream"

std::mutex s_mutex;

void client::connect()
{
    m_socket.async_connect(m_ed, boost::bind(&client::handle_connect, this, boost::asio::placeholders::error));
}

void client::handle_write()
{
    std::string line;
//    std::cout << "enter your data: ";
    std::string ip = m_socket.local_endpoint().address().to_string();
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
        head.checknum = netMsg::makeChceknum(head);
        memcpy(head.info.ip, ip.data(), strlen(ip.data()));
        memcpy(head.info.name, "xwz", 3);
        head.info.times = time(nullptr);
        char buff[1024] = {0};
//        auto buff =  netResolver::generator()->compose(head, line.data(), strlen(line.c_str()));
        netResolver::generator()->compose(head, line.data(), strlen(line.data()), buff);
        m_socket.write_some(boost::asio::buffer(buff, sizeof(head) + strlen(line.data())));
    }
    m_socket.close();
    std::cout << "done!" << std::endl;

}

void client::handle_readhead(boost::system::error_code ec, size_t bytes)
{
    if(ec || bytes == 0)
    {
        std::cerr << boost::format("server close...") << std::endl;
        m_socket.close();
        exit(0);
    }
    if(!netMsg::isVaildChecknum(m_msg.head))
    {
        std::cerr << "handle_readhead | head is not vaild..." << std::endl;
//        m_socket.close();
        return;
    }
    std::memset(m_msg.body, 0, sizeof(m_msg.body));
    m_socket.async_read_some(boost::asio::buffer(m_msg.body, m_msg.head.len), \
        boost::bind(&client::handle_readbody, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void client::handle_readbody(boost::system::error_code ec, size_t bytes)
{
    if(ec)
    {
        std::cerr << boost::format("handle_readbody error, bytes = %d") % bytes << std::endl;
        m_socket.close();
        return;
    }
    if(bytes == 0)
    {
        return;
    }

    std::cout << boost::format("[ip: %s, name: %s, time = %s] read databody(%d): %s") \
        % m_msg.head.info.ip % m_msg.head.info.name % netTimeResolver::getTimeString(m_msg.head.info.times) % bytes % m_msg.body << std::endl;

    m_socket.async_read_some(boost::asio::buffer(&m_msg.head, sizeof(netHead)), boost::bind(&client::handle_readhead, this, \
        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void client::handle_checkConnect()
{
    netHead head;
    head.type = 1;
    head.version = 1;
    head.len = 0;
    head.checknum = netMsg::makeChceknum(head);

    char buff[1024] = {0};
    netResolver::generator()->compose(head, nullptr, 0, buff);

    m_socket.write_some(boost::asio::buffer(buff, sizeof(netHead)));
}

void client::handle_connect(boost::system::error_code ec)
{
    if(!ec)
    {
        using namespace boost::asio;
        handle_checkConnect();
        std::cout << boost::format("connect server successfully: addr = %s") % m_socket.remote_endpoint().address().to_string() << std::endl;
//        boost::asio::async_read(m_socket, boost::asio::buffer(m_buf), boost::bind(&client::handle_read, this, placeholders::error, placeholders::bytes_transferred));

        m_socket.async_read_some(boost::asio::buffer(&m_msg.head, sizeof(netHead)), boost::bind(&client::handle_readhead, this, placeholders::error, placeholders::bytes_transferred));
        std::thread t1(boost::bind(&client::handle_write, this));
        t1.detach();
    }
    else
    {
        std::cerr << boost::format("connect error, msg = %s") % ec.message() << std::endl;
        std::cerr << "reconnect again... wait for 3 secs" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        connect();
    }
}
