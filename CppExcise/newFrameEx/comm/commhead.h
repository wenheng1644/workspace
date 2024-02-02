#ifndef COMMHEAD
#define COMMHEAD

#include "../netcomm/net/netMsg.h"
#include "../netcomm/net/resolveManager.h"

#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_hash.hpp"
#include "boost/uuid/uuid_serialize.hpp"
#include "boost/uuid/uuid_io.hpp"

#include "boost/format.hpp"

#include "mutex"

typedef std::lock_guard<std::mutex> lockGuard_tp;

namespace commStr{
    std::string rec_formatStr(boost::format& f);

    template<typename T, typename... Arg>
    std::string rec_formatStr(boost::format& f, T& v, Arg&... reset);
}



template<typename T, typename... Arg>
std::string commStr::rec_formatStr(boost::format& f, T& v, Arg&... reset)
{
    f = f % v;
    return commStr::rec_formatStr(f, reset...);
}

template<typename... Arg>
std::string getFormatStr(const char* format, const Arg&... reset)
{
    
    boost::format f = boost::format(format);

    return commStr::rec_formatStr(f, reset...);
}

#endif