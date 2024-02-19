//
// Created by wenheng on 23年10月9日.
//

#ifndef LOG_EX_LOGMANAGER_H
#define LOG_EX_LOGMANAGER_H

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include "boost/log/support/date_time.hpp"

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

//#define BOOST_LOG_DYN_LINK 1


class LogManager {
public:
    LogManager();

private:
    void init();
};


#endif //LOG_EX_LOGMANAGER_H
