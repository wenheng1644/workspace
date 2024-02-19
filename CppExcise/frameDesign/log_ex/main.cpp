#include <iostream>

#include "logManager/logManager.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    LogManager LOG;

    BOOST_LOG_TRIVIAL(trace) << "你好";
    BOOST_LOG_TRIVIAL(warning) << "报错";
    return 0;
}
