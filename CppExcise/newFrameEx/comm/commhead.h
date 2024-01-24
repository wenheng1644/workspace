#ifndef COMMHEAD
#define COMMHEAD

#include "../netcomm/net/netMsg.h"
#include "../netcomm/net/resolveManager.h"

#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_hash.hpp"
#include "boost/uuid/uuid_serialize.hpp"

#include "boost/format.hpp"


std::string getFormatStr(boost::format& f)
{
    return f.str();
}

template<typename T, typename... Arg>
std::string getFormatStr(boost::format& f, T& v, Arg&... reset)
{
    f = f % v;
    return getFormatStr(f, reset...);
}

template<typename... Arg>
std::string getFormatStr(const char* format, const Arg&... reset)
{
    
    boost::format f = boost::format(format);

    return getFormatStr(f, reset...);
}

#endif