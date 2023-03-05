//
// Created by 文恒 on 2022/3/6.
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "boost/thread.hpp"



void print(boost::system::error_code e,boost::asio::steady_timer* t, int* count)
{
    if(*count < 5)
    {
        t->expires_at(t->expiry() + boost::asio::chrono::seconds(1));
        ++(*count);

        t->async_wait(boost::bind(print,boost::asio::placeholders::error,t,count));

        std::cout << *count << ": hello guys" << std::endl;
    }


}

class printer
{
public:
    printer(boost::asio::io_context& io) : timer_(io, boost::asio::chrono::seconds(1)),
        count_(0)
    {
        timer_.async_wait(boost::bind(&printer::print,this));
    }

    void print()
    {
        if(count_ < 5)
        {
            timer_.expires_at(timer_.expiry() + boost::asio::chrono::seconds(1));
            ++count_;
            timer_.async_wait(boost::bind(&printer::print,this));

            std::cout << count_ << ": I like you~" << std::endl;
        }


    }

    ~printer()
    {
        std::cout << "object gone, and this count: " << count_ << std::endl;
    }

private:
    boost::asio::steady_timer timer_;
    int count_;

};

void hello()
{
    std::cout << "hello guys" << std::endl;
}

void testBoostThd()
{
    boost::thread thd(&hello);
    thd.join();
}

int main()
{
//    int count = 0;
//    boost::asio::io_context io;
//    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
//
//    t.async_wait(boost::bind(print,boost::asio::placeholders::error,&t,&count));
//
//    io.run();
//
//    std::cout << "the last count: " << count << std::endl;

//    boost::asio::io_context io;
//
//    printer p(io);
//
//    io.run();

    testBoostThd();
    return 0;
}


