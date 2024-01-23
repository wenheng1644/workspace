#ifndef RESOLVEMANAGER
#define RESOLVEMANAGER

#include "../chatcmd/chatcmd.pb.h"

template<typename T>
std::string serlizeCmdToStr(T* cmd)
{
    assert(cmd != nullptr);

    std::string str = cmd->SerializeAsString();

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

#endif