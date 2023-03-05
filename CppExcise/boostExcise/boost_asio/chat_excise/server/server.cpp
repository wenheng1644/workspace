//
// Created by 文恒 on 2022/4/10.
//

#include "server.h"
#include "chatMsg.h"
void server::run()
{
    chatMsg_ptr ptr(new chatMsg(m_ioserver));
    m_acceptor.async_accept(ptr->socket(), boost::bind(&server::handle_connect, this, ptr));
}

void server::handle_readBody(chatMsg_ptr chatMsgPtr) {

}

void server::handle_connect(chatMsg_ptr ptr)
{
    std::cout << "connect..." << std::endl;
    auto p = [this,&ptr]()
    {
        run();
        while(true)
        {
            char buff[6] = {};
            boost::system::error_code ec;
            boost::asio::read(ptr->socket(), buffer(buff, sizeof(msgHeader)), ec);

            if(ec)
            {
                std::lock_guard<std::mutex> lg(m_mutex);
                std::cout << "header error..." << std::endl;

                ptr->socket().close();
                return ;
            }

            msgHeader header = *(msgHeader*)buff;
            if(header.bodySize == 0)
            {
                std::lock_guard<std::mutex> lg(m_mutex);
                std::cerr << "bodySize error" << std::endl;
                ptr->socket().close();
                return ;
            }

            boost::system::error_code body_ec;
            char body[512] = {};
            boost::asio::read(ptr->socket(), buffer(body, header.bodySize), body_ec);

            if(body_ec)
            {
                std::lock_guard<std::mutex> lg(m_mutex);
                std::cerr << "body error" << std::endl;
                ptr->socket().close();

                return ;
            }

            {
                std::lock_guard<std::mutex> lg(m_mutex);
                std::cout << "body content: " << body << std::endl;
            }
        }

    };

    std::thread t1(p);
    t1.join();
}


