//
// Created by 文恒 on 24-10-8.
//

#ifndef CONN_H
#define CONN_H

#include "boost/asio.hpp"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_io.hpp"

// #include  "boost/enable_shared_from_this.hpp"

#include "NetData.h"

using boost::asio::ip::tcp;

class Conn : public std::enable_shared_from_this<Conn>
{
public:
    enum TYPE
    {
        LISTEN = 1,
        CLIENT = 2,
    };


    Conn(boost::asio::io_service& io_service);
    ~Conn() = default;

    tcp::socket& socket()
    {
        return m_socket_;
    }
    void run();
    void close();
    void write(const std::string& data);
public:
    int m_typ;              //socket类型 ---> 监听/普通客户端
    u_int32_t m_server_id;    //关联的服务id
    boost::uuids::uuid m_uuid;     //唯一标识
private:
    tcp::socket m_socket_;          //socket套接字


private:
    void OnReadHeader(std::shared_ptr<NetData> net_data, u_int32_t srvid, boost::system::error_code ec, size_t bytes) ;
    void OnReadBody(std::shared_ptr<NetData> net_data, u_int32_t srvid,  boost::system::error_code ec, size_t bytes) ;


};

#endif //CONN_H
