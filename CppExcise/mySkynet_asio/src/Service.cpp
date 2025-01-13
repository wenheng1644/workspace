//
// Created by 文恒 on 24-10-7.
//

#include "Service.h"

#include <iostream>
#include <Sunnet.h>
#include <boost/uuid/random_generator.hpp>

#include "boost/uuid/uuid_io.hpp"
#include "boost/json.hpp"

void Service::OnInit(sol::variadic_args& args)
{
    std::cout << "Service::OnInit: " << m_id << std::endl;

    m_lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string, sol::lib::table, sol::lib::ffi, sol::lib::math);
    LuaAPI::Register(m_lua);

    std::string file = "../server/" + *m_type + "/init.lua";

    sol::load_result result = m_lua.load_file(file.c_str());

    if(result.valid())
    {
        std::cout << "Service::OnInit  load success" << std::endl;

        std::vector<sol::object> params;
        sol::object lua_m_id = make_object(m_lua, m_id);
        params.push_back(lua_m_id);

        for (auto v : args)
            params.push_back(v);

        result(sol::as_args(params));
        sol::function init = m_lua["OnInit"];

        if(init.valid())
        {
            init(m_id, args);
        }
        else
        {
            printf("Service::OnInit  load failed\n");
        }
    }
    else
    {
        std::cerr << "Service::OnInit  load failed" << std::endl;
    }
}

void Service::OnMsg(std::shared_ptr<BaseMsg> msg)
{
    std::cout << "Service::OnMsg" << std::endl;

    int msg_type = msg->m_type;
    if(msg_type == BaseMsg::TYPE::SOCKET_ACCEPT)
    {
        std::shared_ptr<SocketAcceptMsg> accept_msg = std::dynamic_pointer_cast<SocketAcceptMsg>(msg);
        OnSocketAccept(accept_msg);
    }
    else if(msg_type == BaseMsg::TYPE::SOCKET_RW)
    {
        std::shared_ptr<SocketRWMsg> rw_msg = std::dynamic_pointer_cast<SocketRWMsg>(msg);
        OnSocketRW(rw_msg);
    }
    else if (msg_type == BaseMsg::TYPE::SOCKET_CLOSE)
    {
        std::shared_ptr<SockectCloseMsg> close_msg = std::dynamic_pointer_cast<SockectCloseMsg>(msg);
        OnSocketClose(close_msg);
    }
    else if(msg_type == BaseMsg::TYPE::SERVICE)
    {
        std::shared_ptr<ServiceMsg> service_msg = std::dynamic_pointer_cast<ServiceMsg>(msg);
        OnServerMsg(service_msg);
    }
}

void Service::OnExit()
{
    std::cout << "Service::OnExit" << std::endl;
}

void Service::OnSetConfig(const ServerArgs& args)
{
    m_config = std::make_shared<ServerArgs>(args);
}

void Service::PushMsg(std::shared_ptr<BaseMsg> msg)
{
    {
        std::lock_guard<std::mutex> lock_guard(m_queueMutex);
        m_MsgQueue.push(msg);
    }
}

bool Service::ProcessMsg()
{
    auto msg = PopMsg();
    if(!msg) return false;

    OnMsg(msg);

    return true;
}

void Service::ProcessMsgs(int max)
{
    for(int i = 0; i < max; i++)
    {
        bool success = ProcessMsg();
        if(!success)
            break;
    }
}

void Service::SetInGlobal(bool inGlobal)
{
    {
        std::lock_guard<std::shared_mutex> lock_guard(m_InGlobalMutex);
        m_InGlobal = inGlobal;
    }
}

std::shared_ptr<BaseMsg> Service::PopMsg()
{
    std::shared_ptr<BaseMsg> msg = nullptr;
    {
        std::lock_guard<std::mutex> lock_guard(m_queueMutex);
        if(!m_MsgQueue.empty())
        {
            msg = m_MsgQueue.front();
            m_MsgQueue.pop();
        }
    }

    return msg;
}

void Service::OnSocketAccept(std::shared_ptr<SocketAcceptMsg> msg)
{
    std::cout << "[C++]Service: new conn ---> " << msg->m_socket_uuid << std::endl;

    std::string uuid_str = boost::uuids::to_string(msg->m_socket_uuid);

    sol::function func = m_lua["net_dispatcher"];
    sol::type t = func.get_type();
    func(ACCEPT, uuid_str.c_str());
}

void Service::OnSocketRW(std::shared_ptr<SocketRWMsg> msg)
{
    std::cout << "Service::OnSocketRW | len(m_datas) = " << strlen(msg->m_datas.c_str()) << ", len2 = " << msg->m_datas.length() << std::endl;

    sol::function func = m_lua["net_dispatcher"];
    func(DATA, msg->m_socket_uuid_str.c_str(), msg->m_datas.c_str());
}

void Service::OnSocketClose(std::shared_ptr<SockectCloseMsg> msg)
{
    std::cout << "Service::OnSocketClose | close  id = " << m_id << std::endl;
    sol::function func = m_lua["net_dispatcher"];
    func(CLOSE, msg->m_socket_uuid_str.c_str());
}

void Service::OnServerMsg(std::shared_ptr<ServiceMsg> msg)
{
    std::cout << "[C++]Service: get other server datas ---> " << msg->m_source << std::endl;

    sol::function func = m_lua["OnServerMsg"];
    if (func.valid() && func.get_type() == sol::type::function)
    {
        std::vector<sol::object> args;
        for (auto v : msg->args)
        {
            if (v.is<std::string>())
            {
                std::string s = v.as<std::string>();
                sol::object obj = sol::make_object(m_lua, s);
                args.push_back(obj);
            }
            else
            {
                args.push_back(v);
            }
        }
        func(msg->m_source,  sol::as_args(args));
    }
    else
        std::cout << "[C++]Service: OnServerMsg error" << std::endl;
}

