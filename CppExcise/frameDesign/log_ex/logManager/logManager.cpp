//
// Created by wenheng on 23年10月9日.
//

#include "logManager.h"

LogManager::LogManager()
{
    init();
}

void LogManager::init()
{
    // 设置日志格式
//    typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink;
//    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();

    logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");
//    expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f");
    // 创建控制台 sink
    auto console_sink = logging::add_console_log(std::cout);
    console_sink->set_formatter(expr::format("[%1%](%2%) threadID = %3%: %4%") % expr::attr<logging::trivial::severity_level>("Severity") \
            %expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S") % expr::attr<attrs::current_thread_id::value_type>("ThreadID") %expr::smessage);


    // 创建文件 sink
    auto file_sink = logging::add_file_log(
            keywords::file_name = "sample_%Y-%m-%d_%N.log",
            keywords::rotation_size = 10 * 1024 * 1024,
            keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
            keywords::format = expr::format("[%1%](%2%) %3%") % expr::attr<logging::trivial::severity_level>("Severity") \
                    %expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")% expr::smessage
    );

    file_sink->set_filter(logging::trivial::severity >= logging::trivial::info);

    // 设置日志级别
    console_sink->set_filter(logging::trivial::severity >= logging::trivial::trace);

    // 添加公共属性
    logging::add_common_attributes();
}



