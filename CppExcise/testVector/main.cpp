//
// Created by wenheng on 22-10-30.
//
#include "myVector.h"
#include "iostream"

#include "boost/format.hpp"

void test_alloctor()
{
    myVector<int> vals{1,2,3,4};
    vals.push_back(5);
    std::cout << "size = " << vals.size() << std::endl;
    std::cout << vals[2] << std::endl;
    myVector<int> temp(vals);
    vals.insert(vals.begin() + 1, 111);
    vals.insert(vals.begin() + 1, {223, 334, 556});
    std::cout << "cap = " << vals.capactiy() << std::endl;
    for(auto& v : vals)
    {
        std::cout << v << " ";
    }
    vals.insert(vals.begin(), {2022, 2023, 2024});
    std::cout << "\n" << "new cap = " << vals.capactiy() << std::endl;
    for(auto& v : vals)
    {
        std::cout << v << " ";
    }

    std::cout << std::endl;
    if(vals.find(2022))
        std::cout << "find it" << std::endl;
    std::cout << "大范围数据测试" << std::endl;
    for(int i = 2000; i < 30000; i++)
        vals.push_back(i);

    std::cout << boost::format("size = %d and cap = %d") % vals.size() % vals.capactiy() << std::endl;
    vals[-1];
}

int main()
{
    test_alloctor();
    return 0;
}
