//
// Created by 文恒 on 24-10-7.
//

#ifndef MSG_H
#define MSG_H

// #pragma pack(push, 1)
// #pragma once
#include <sys/types.h>
#include <memory>
#include <boost/uuid/uuid.hpp>
#include <sys/_types/_u_int.h>

#include "boost/asio.hpp"
#include "sol/sol.hpp"


using boost::asio::ip::tcp;

class BaseMsg
{
public:
  enum TYPE
  {
      SERVICE = 1,
      SOCKET_ACCEPT = 2,
      SOCKET_RW = 3,
      SOCKET_CLOSE = 4,
  };

    u_int8_t m_type;
    BaseMsg(u_int8_t type): m_type(type) {}
    BaseMsg() : m_type(0) {}
    virtual ~BaseMsg() = default;
};


class ServiceMsg : public BaseMsg
{
public:
    uint32_t m_source;
    std::vector<sol::object> args;
};

class SocketAcceptMsg : public BaseMsg
{
public:
    boost::uuids::uuid m_socket_uuid;   //连接进来的socket标识符
    // tcp::socket m_listen_fd;
    // tcp::socket m_client_fd;
    // int  m_listen_fd;
    // int  m_client_fd;
};

class SocketRWMsg : public BaseMsg
{
public:
    std::string m_datas;            //网络数据
    std::string m_socket_uuid_str;         //socket句柄 uid
};


class SockectCloseMsg : public BaseMsg
{
public:
    std::string m_socket_uuid_str;         //socket句柄 uid
};
#endif //MSG_H
