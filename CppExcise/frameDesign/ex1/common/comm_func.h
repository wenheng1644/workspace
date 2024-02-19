//
// Created by wenheng on 23年10月10日.
//

#ifndef EX1_COMM_FUNC_H
#define EX1_COMM_FUNC_H

#include "string"

#include "boost/format.hpp"

namespace commfunc
{
    template<typename... Args>
    std::string getFormatStr(const char* format, const Args&...args);

    template<typename  T,typename... Args>
    boost::format& recursionFormat(boost::format& f, const T& v, const Args&...args);

    boost::format& recursionFormat(boost::format& f);
}
template<typename  T,typename... Args>
boost::format& commfunc::recursionFormat(boost::format& f, const T& v, const Args&...args)
{
    boost::format temp = f % v;

    return commfunc::recursionFormat(f, args...);
}

template<typename... Args>
std::string commfunc::getFormatStr(const char* format, const Args&...args)
{
    boost::format f = boost::format(format);
    boost::format ans = recursionFormat(f, args...);

    std::string str = ans.str();

    return str;
}


#endif //EX1_COMM_FUNC_H
