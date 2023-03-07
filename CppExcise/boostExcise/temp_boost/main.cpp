//
// Created by wenheng on 2022/4/21.
//

#include "iostream"

#include "boost/filesystem.hpp"

int main()
{
    boost::filesystem::path mypath(".");

    std::cout << mypath.parent_path() << std::endl;
    std::cout << mypath.stem() << std::endl;

    return 0;
}