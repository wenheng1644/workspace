#ifndef RESOLVEMANAGER
#define RESOLVEMANAGER

#include "../chatcmd/chatcmd.pb.h"
#include "netMsg.h"

template<typename T>
std::string serlizeCmdToStr(T cmd)
{
    // assert(cmd != nullptr);

    std::string str;
    cmd.SerializeToString(&str);

    return str;
}

template<typename T>
T parseSerlizeStr(const std::string& str)
{
    assert(!str.empty());
    
    T cmd;
    cmd.ParseFromString(str);

    return cmd;
}


//将网络包序列化
std::string getSerlizeNetMsgStr(const netMsg&);

#endif