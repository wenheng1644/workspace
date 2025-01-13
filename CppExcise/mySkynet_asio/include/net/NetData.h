//
// Created by 文恒 on 24-10-10.
//

#ifndef NETDATA_H
#define NETDATA_H

#pragma pack(push, 1)
#pragma once
#include <sys/_types/_u_char.h>
#include <sys/_types/_u_int16_t.h>
#include <sys/_types/_u_int32_t.h>

#include <string>

#include <memory>

//网络数据类型
enum Net_TYPE
{
    ACCEPT = 1, //监听
    DATA = 2,   //读数据
    CLOSE = 3,  //关闭
};

struct NetHeader
{
    u_char      type_id;        //主协议id
    u_char      type_subid;     //子协议id
    u_char      version;        //协议版本号 （暂时为1）
    u_int32_t   body_length;    //消息体(NetBody)字节大小
    u_int32_t   offset;         //TCP验证码 = (version << 32) | (type_id << 8) | (type_subid)

    static bool check(const NetHeader& header);
    static u_int32_t makeOffset(const NetHeader& header);
    static void setOffset(NetHeader& header);
};

//校验是否完整合法的数据头结构
inline bool NetHeader::check(const NetHeader& header)
{
    u_int32_t ret = 0;
    ret = makeOffset(header);

    return (ret == header.offset);
}

inline u_int32_t NetHeader::makeOffset(const NetHeader& header)
{
    u_int32_t ret = (header.version << 16) | (header.type_id << 8) | header.type_subid;
    return ret;
}

inline void NetHeader::setOffset(NetHeader& header)
{
    header.offset = makeOffset(header);
}


struct NetBody
{
    u_char      type_id;        //主协议id
    u_char      type_subid;     //子协议id
    u_int16_t   offset;         //校验码 = (type_id << 8) | type_subid
    std::string  buff; //实际业务数据

    static bool check(const NetBody& body);
    static void setOffset(NetBody& body);
    static u_int16_t makeOffset(const NetBody& body);
};

inline bool NetBody::check(const NetBody& body)
{
    u_int16_t ret = 0;
    ret = makeOffset(body);

    return (ret == body.offset);
}

inline void NetBody::setOffset(NetBody& body)
{
    body.offset = makeOffset(body);
}

inline u_int16_t NetBody::makeOffset(const NetBody& body)
{
    u_int16_t ret = (body.buff.length() << 16) | (body.type_id << 8) | body.type_subid;
    return ret;
}


struct NetData
{
    NetHeader header;
    NetBody body;
};

#pragma pack(pop)
#endif //NETDATA_H
