//
// Created by 文恒 on 24-10-7.
//

#ifndef SERVICE_H
#define SERVICE_H

#pragma once

// #include <thread>
#include <mutex>
// #include <condition_variable>
#include <queue>
#include <shared_mutex>

#include "Msg.h"

#include "LuaAPI.h"

#include "sol/sol.hpp"

struct  ServerArgs
{
    bool isListen;      //是否监听服务
    std::string ip;     //关联的ip
    int port;           //关联的端口
    int config_id;      //关联的配置id

    bool get_isListen() {return isListen;}
    void set_isListen(bool isListen_) {isListen = isListen_;}

    std::string getIp() {return ip;}
    void setIp(std::string ip_) {ip = ip_;}
    int getPort() {return port;}
    void setPort(int port_) {port = port_;}
    int getConfigId() {return config_id;}
    void setConfigId(int config_id_) {config_id = config_id_;}

    ServerArgs() = default;

    ~ServerArgs() = default;
};


class Service
{
public:
    u_int32_t m_id;
    u_int32_t m_config_id;
    std::shared_ptr<ServerArgs> m_config;
    std::shared_ptr<std::string> m_type;

    bool m_isExisting = false;

    std::queue<std::shared_ptr<BaseMsg>> m_MsgQueue;
    std::mutex m_queueMutex;

    bool m_InGlobal = false;
    std::shared_mutex m_InGlobalMutex;
private:
    // lua_State* m_luaState;
    sol::state m_lua;
public:
    Service() = default;
    ~Service() = default;

    //回调函数
    void OnInit(sol::variadic_args& args);
    void OnMsg(std::shared_ptr<BaseMsg> msg);
    void OnExit();

    void OnSetConfig(const ServerArgs& args);
    //插入消息
    void PushMsg(std::shared_ptr<BaseMsg> msg);

    //执行消息
    bool ProcessMsg();
    void ProcessMsgs(int max);

    void SetInGlobal(bool inGlobal);

private:
    //取出消息
    std::shared_ptr<BaseMsg> PopMsg();

    void OnSocketAccept(std::shared_ptr<SocketAcceptMsg> msg);
    void OnSocketRW(std::shared_ptr<SocketRWMsg> msg);
    void OnSocketClose(std::shared_ptr<SockectCloseMsg> msg);
    void OnServerMsg(std::shared_ptr<ServiceMsg> msg);

};


#endif //SERVICE_H
