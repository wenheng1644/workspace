//
// Created by 文恒 on 2022/4/12.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <iostream>

#include "boost/asio.hpp"
#include "boost/bind/bind.hpp"

#include "../server/chatMsg.h"
#include "dispatch.h"

#include "QObject"
//class myDispatch;

using namespace boost::asio;

class chat_client : public QObject
{
    Q_OBJECT
public:
    chat_client(boost::asio::io_service& io_service, // 1
                ip::tcp::resolver::iterator endpoint_iterator)
            : io_service_(io_service),
              socket_(io_service), m_endpoint_iterator(endpoint_iterator)
    {
//        ip::tcp::endpoint endpoint = *endpoint_iterator;
//        memset(read_msg_.getData(), 0, HEADER_LEN + BODY_LEN);
//        socket_.async_connect(endpoint,
//                              boost::bind(&chat_client::handle_connect, this, // 2
//                                          boost::asio::placeholders::error, ++endpoint_iterator));

        std::cout << "chat_client thread id: " << std::this_thread::get_id() << std::endl;        
    }

    void write(const chatMsg& msg) // 5
    {
        std::cout << "write thread id: " << std::this_thread::get_id() << std::endl;
        io_service_.post(boost::bind(&chat_client::do_write, this, msg));
//        io_service_.run();
    }

    void close()
    {
        io_service_.post(boost::bind(&chat_client::do_close, this));
    }

    void connect()
    {

        ip::tcp::endpoint endpoint = *m_endpoint_iterator;
        memset(read_msg_.getData(), 0, HEADER_LEN + BODY_LEN);

        boost::system::error_code ec;
        socket_.async_connect(endpoint, boost::bind(&chat_client::handle_connect, this, boost::asio::placeholders::error, m_endpoint_iterator));
//        socket_.connect(endpoint, ec);

//        std::cout << "connect thread id: " << std::this_thread::get_id() << std::endl;
//        if(!ec)
//        {
////            syn_readheader(ec);
//            handle_connect(ec, m_endpoint_iterator);

//            return true;
//        }
//        else
//        {
//            return false;
//        }
    }

    void UserName(std::string& username)
    {
        m_username = username;
    }

    std::string UserName()
    {
        return m_username;
    }

    void handle_connect(const boost::system::error_code& error, // 2
                        ip::tcp::resolver::iterator endpoint_iterator)
    {
        std::cout << "handle_connect thread id: " << std::this_thread::get_id() << std::endl;
        if (!error)
        {
//            boost::asio::read(socket_, buffer(read_msg_.getData(), HEADER_LEN));
            emit signal_connect(true);
            chatMsg headMsg = makeHeadMsg();
            write(headMsg);
            boost::asio::async_read(socket_,
                                    boost::asio::buffer(read_msg_.getData(), HEADER_LEN),  //copy buffer to read_msg_'s header
                                    boost::bind(&chat_client::handle_read_header, this, // 3
                                                boost::asio::placeholders::error));
//            io_service_.run();
        }
        else if (endpoint_iterator != ip::tcp::resolver::iterator())
        {
            socket_.close();
            ip::tcp::endpoint endpoint = *endpoint_iterator;
            socket_.async_connect(endpoint,
                                  boost::bind(&chat_client::handle_connect, this, // 2
                                              boost::asio::placeholders::error, ++endpoint_iterator));
//            connect();
//            io_service_.run();
        }
        else if(error)
        {
            socket_.close();
            emit signal_connect(false);
            std::cerr << "server connect error..." << std::endl;
            return;
        }
    }
private:



    void handle_read_header(const boost::system::error_code& error) // 3
    {
        std::cout << "handle_read_head thread id: " << std::this_thread::get_id() << std::endl;
        if (!error && read_msg_.decode())
        {
            boost::asio::async_read(socket_,
                                    boost::asio::buffer(read_msg_.body(), read_msg_.bodyLen()), //copy buffer to read_msg_'s body
                                    boost::bind(&chat_client::handle_read_body, this, // 4
                                                boost::asio::placeholders::error));
//            io_service_.run();
        }
        else
        {
            do_close();
        }
    }

    void handle_read_body(const boost::system::error_code& error) // 4
    {
        std::cout << "handle_read_body thread id: " << std::this_thread::get_id() << std::endl;
        if (!error)
        {
            std::cout << read_msg_.body() << std::endl; // print read_msg_'s body
//            myDispatch::getSington()->sendMsg(read_msg_.body());
//            emit myDispatch::getSington()->signal_sendmsg(std::string(read_msg_.body()));
            QString msg(read_msg_.body());
            emit signal_sendMsg(msg);
            memset(read_msg_.getData(), 0 ,HEADER_LEN + BODY_LEN);
            boost::asio::async_read(socket_,
                                    boost::asio::buffer(read_msg_.getData(), HEADER_LEN),
                                    boost::bind(&chat_client::handle_read_header, this, // 4
                                                boost::asio::placeholders::error));

//            io_service_.run();
        }
        else
        {
            do_close();
        }
    }

    void do_write(chatMsg msg) // 6
    {
        std::cout << "do_write thread id: " << std::this_thread::get_id() << std::endl;
        bool write_in_progress = !write_msgs_.empty();
        write_msgs_.push_back(msg);
        if (!write_in_progress)
        {
            boost::asio::async_write(socket_,
                                     boost::asio::buffer(write_msgs_.front().getData(),
                                                         write_msgs_.front().getLen()), // copy write_msgs_.front() to buffer
                                     boost::bind(&chat_client::handle_write, this, // 7 send message
                                                 boost::asio::placeholders::error));
        }
    }

    void handle_write(const boost::system::error_code& error) // 7
    {
        std::cout << "handle_write thread id: " << std::this_thread::get_id() << std::endl;
        if (!error)
        {
            write_msgs_.pop_front();
            if (!write_msgs_.empty())
            {
                boost::asio::async_write(socket_,
                                         boost::asio::buffer(write_msgs_.front().getData(),
                                                             write_msgs_.front().getLen()),
                                         boost::bind(&chat_client::handle_write, this, // 7
                                                     boost::asio::placeholders::error));
            }
        }
        else
        {
            do_close();
        }
    }

    void do_close()
    {
        socket_.close();
//        emit signal_sendMsg(QString("与服务器断开连接"));

//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//        sleep(1);
//        close();
        return;
    }


    void syn_readheader(boost::system::error_code ec)
    {
        if(ec)
        {
            std::cerr << "read header error" << std::endl;
            do_close();
            return;
        }

        if(!read_msg_.decode())
        {
            std::cerr << "decode header error..." << std::endl;
            do_close();
            return;
        }

//        myDispatch::getSington()->sendMsg(read_msg_.body());
        memset(read_msg_.getData(), 0 ,HEADER_LEN + BODY_LEN);

//        syn_readheader();
    }

    //发送连接头部消息
    chatMsg makeHeadMsg()
    {
        chatMsg headMsg;
        size_t userName_len = strlen(m_username.c_str());
        headMsg.bodyLen(userName_len);
        headMsg.encode();
        memcpy(headMsg.body(), m_username.c_str(), userName_len);

        return headMsg;
    }

private:
    boost::asio::io_service& io_service_;
    ip::tcp::socket socket_;
    chatMsg read_msg_;  // 存从buffer读出的数据
    chatMsg_queue write_msgs_; // 欲写入buffer的数据队列，deque
    std::string m_username;
    ip::tcp::resolver::iterator m_endpoint_iterator;

signals:
    void signal_sendMsg(QString msg);
    void signal_disconnect();
    void signal_connect(bool connected);
};


#endif //CLIENT_CLIENT_H
