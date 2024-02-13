#ifndef NETMSG
#define NETMSG

#include "iostream"
#include "string"
#include "cstring"
#include "memory"

// #include "../netcommhead.h"

#define MEMZERO (memset((this), 0, sizeof(*this)))
#pragma pack(1)
//网络包消息头
struct netHead
{
    u_char      type;       //主协议id
    u_char      subtype;    //副协议id
    u_int32_t       len;        //数据体长度
    u_int64_t      sendtime;   //发送的时间戳
    u_char      version;    //版本号(目前没用到)
    u_short     checkcode;  //校验码

    netHead()
    {
        MEMZERO;
    }

    netHead(u_char dataType, u_char dataSubType, u_int bodyLen = 0);

    netHead& operator=(const netHead& other);

    size_t getProtoValue() const { return ((type << 8 ) | subtype);}

    ~netHead() = default;

    static u_short makecheckcode(const netHead& head);      //创建校验码
    static bool isvaildcheckcode(const netHead& head);      //检查校验码是否合法
};
#pragma pack()


//网络包结构体
struct netMsg
{
    netHead head;           //数据头
    std::string datas;      //数据体

    netMsg() : head(netHead()), datas(std::string()) {}
    netMsg(const netHead& datahead) : head(datahead), datas(std::string()) {}
    netMsg(u_char dataType, u_char dataSubType) : head(dataType, dataSubType), datas(std::string()) {}
    netMsg(u_char dataType, u_char dataSubType, const std::string& serStr);
    netMsg(const netMsg& other);
    netMsg& operator=(const netMsg& other);

    ~netMsg() = default;
};

typedef typename std::shared_ptr<netMsg> netMsg_ptr;

#endif