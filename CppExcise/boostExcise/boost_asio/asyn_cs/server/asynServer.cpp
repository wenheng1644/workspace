#include "asynServer.h"

void asynServer::start()
{
    boost::shared_ptr<ip::tcp::socket> psocket(new ip::tcp::socket(m_ioserver));
    

    m_acceptor.async_accept(*psocket ,boost::bind(&asynServer::connect_callback, this, psocket, boost::placeholders::_1));

}

void asynServer::connect_callback(boost::shared_ptr<ip::tcp::socket> psocket, boost::system::error_code ec)
{
    if(ec) return;

    start();

    std::cout << "remote ip: " << psocket->remote_endpoint().address() << std::endl;

    boost::shared_ptr<std::string> pstr(new std::string("connect server successful"));

    psocket->async_write_some(buffer(*pstr), boost::bind(&asynServer::sendMsg_callback, this, boost::placeholders::_1, boost::placeholders::_2));
    std::cout << "async_write_some() done..." << std::endl;

}


void asynServer::sendMsg_callback(boost::system::error_code ec, size_t bytes)
{
    if(ec)
    {
        std::cout << "server Error..." << std::endl;
    }
    else
    {
        std::cout << "send finish: " << bytes << std::endl;
    }
}