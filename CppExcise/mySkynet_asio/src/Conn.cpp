//
// Created by 文恒 on 24-10-8.
//

#include "Conn.h"

#include <iostream>

#include <functional>
#include <Sunnet.h>

Conn::Conn(boost::asio::io_service& io_service) : m_socket_(io_service), m_uuid(boost::uuids::random_generator()())
{

}

void Conn::run()
{
    std::cout << "Conn::run() --> uuid = " << m_uuid << std::endl;

    std::shared_ptr<NetData> net_data(new NetData);
    auto handler = std::bind(&Conn::OnReadHeader, shared_from_this(), net_data, m_server_id, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred);

    m_socket_.async_read_some(boost::asio::buffer(&(net_data->header), sizeof(net_data->header)), handler);
}

void Conn::close()
{
    std::shared_ptr<SockectCloseMsg> msg = std::make_shared<SockectCloseMsg>();
    msg->m_type = BaseMsg::TYPE::SOCKET_CLOSE;
    msg->m_socket_uuid_str = boost::uuids::to_string(m_uuid);

    printf("Conn::close() --> uuid = %s, svrid = %d, send socketClose msg\n", msg->m_socket_uuid_str.c_str(), m_server_id);
    Sunnet::inst->Send(m_server_id, msg);

    m_socket_.close();
}

void Conn::write(const std::string& data)
{
    // std::shared_ptr<NetData> net_data(new NetData);
    // m_socket_.async_write_some()
}

void Conn::OnReadHeader(std::shared_ptr<NetData> net_data, u_int32_t srvid, boost::system::error_code ec, size_t bytes)
{
    if (ec)
    {
        std::cout << ec.message() << std::endl;
        close();
        return;
    }

    if(!NetHeader::check(net_data->header))
    {
        std::cerr << "Invalid NetHeader" << std::endl;
        close();
        return;
    }

    auto handler = std::bind(&Conn::OnReadBody, shared_from_this(), net_data, srvid, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred);
    int bodylen = net_data->header.body_length;
    net_data->body.buff.resize(bodylen - 4, 0);
    m_socket_.async_read_some(boost::asio::buffer(&(net_data->body), net_data->header.body_length), handler);
}

void Conn::OnReadBody(std::shared_ptr<NetData> net_data, u_int32_t srvid, boost::system::error_code ec, size_t bytes)
{
    if(ec)
    {
        std::cerr << ec.message() << std::endl;
        close();
        return;
    }

    if(!NetBody::check(net_data->body))
    {
        std::cerr << "Invalid NetBody" << std::endl;
        close();
        return;
    }

    //TO-DO 打包业务数据推送给服务处理
    std::shared_ptr<SocketRWMsg> msg = std::make_shared<SocketRWMsg>();
    msg->m_type = BaseMsg::TYPE::SOCKET_RW;
    msg->m_datas = net_data->body.buff;
    msg->m_socket_uuid_str = boost::uuids::to_string(m_uuid);

    Sunnet::inst->Send(srvid, msg);
    //继续异步读数据
    run();

}
