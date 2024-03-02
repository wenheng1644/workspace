#include <iostream>
#include "noneClassTemplate.h"
#include "mulArgTemplate.h"

void test_ex1()
{
    Stack<std::string, 10> datas;

    std::cout << "now size = " << datas.size() << std::endl;
    std::cout << "max size = " << datas.max_size() << std::endl;

    datas.push("hello world");

    using Stack_valueTp = Stack<std::string, 10>::value_tp;

    Stack_valueTp v1 = datas.top();

    std::cout << "v1 = " << v1 << std::endl;
}

void test_ex2()
{
    std::string s1("world");

    print(1, 2.2, "hello", s1);
}

int main() {

    test_ex2();

    // std::cout << "Hello, World!" << std::endl;
    return 0;
}
