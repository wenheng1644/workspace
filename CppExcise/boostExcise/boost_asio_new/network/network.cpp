//
// Created by wenheng on 23-3-25.
//

#include "network.h"

void Session::read()
{
    using namespace boost::system;
    auto self(shared_from_this());
    m_sessionSocket.async_read_some(boost::asio::buffer(m_data), [this, self](error_code ec, size_t len){
        auto ed = m_sessionSocket.remote_endpoint();
        std::cout << boost::format("addr = %s, port = %d, len = %d") % ed.address().to_string() % ed.port() % len << std::endl;
        if(len == 0)
        {
            std::cout << boost::format("addr = %s, port = %d disconnected") % ed.address().to_string() % ed.port() << std::endl;
            return;
        }
        if(!ec)
        {
            std::shared_ptr<netMsg> msg = netResolver::generator()->resolver(m_data.data(), len);
            if(true)
            {
                std::cout << boost::format("(addr = %s port = %d) read data(%d : %d): %s") \
                   % ed.address().to_string() % ed.port() \
                    % len %(len - sizeof(netHead)) % std::string(msg->body) << std::endl;
            }
            write(len);
        }
    });
}


void Session::write(size_t len)
{
    using namespace boost::system;
    auto self(shared_from_this());
    m_sessionSocket.async_write_some(boost::asio::buffer(m_data, len), [this, self](error_code ec, size_t len)
    {
        std::cout << "write some data = " << len << std::endl;
        if(!ec)
        {
//            netHead head;
//            std::shared_ptr<char> body = s_resolver.resolver(m_data.data(), len - sizeof(netHead), head);
//            auto data = s_resolver.compose(head, body.get(), m_data.size() - sizeof(head));
            memset(m_data.data(), 0, m_data.size());
            read();
        }
    });

}

void network::run()
{
    using namespace boost::system;
    std::cout << "start to listen" << std::endl;
    m_acceptor.async_accept(m_socket, [this](error_code ec)
    {
        if(!ec)
        {
//            std::cout << "a new client connect..." << std::endl;
            auto addr = m_socket.remote_endpoint().address();
            auto port = m_socket.remote_endpoint().port();
            std::cout << boost::format("new connect: addr = %s, port = %d") % addr.to_string() % port << std::endl;
            std::make_shared<Session>(std::move(m_socket))->start();
        }
        run();
    });

}
