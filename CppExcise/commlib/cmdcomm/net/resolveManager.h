#ifndef RESOLVEMANAGER
#define RESOLVEMANAGER

#include "netMsg.h"
#include "assert.h"

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

class netMsg;

//将网络包序列化
std::string getSerlizeNetMsgStr(const netMsg&);

#endif