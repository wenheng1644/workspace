#include <iostream>
#include "functionCAllBack.h"
#include <boost/bind.hpp>
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"

#include <vector>
#include <iostream>

using namespace boost::lambda;

typedef void (functionCAllBack::*function_p)(int, int);

bool print(int v)
{
    std::cout << "the value: " << v << std::endl;
}

int printBind(int a, bool b, double c)
{
    std::printf("a: %d\tb: %d\tc: %f\n", a, b, c);
    return a + b +c ;
}

int main() {
//    std::cout << "Hello, World!" << std::endl;
//    functionCAllBack obj(&print);
//
//    obj.callback(10);
//
//    function_p p = &functionCAllBack::calc;
//
//    obj.calc(1,2);
//    (obj.*p)(1, 2);
//
//    boost::function<void (int, int)> p2=  boost::bind(&functionCAllBack::calc,&obj, boost::placeholders::_1, boost::placeholders::_2) ;
//    std::function<void (int, int)> p3 = std::bind(&functionCAllBack::calc, &obj, std::placeholders::_1, std::placeholders::_2);
//    p2(1, 2);
//    p3(1, 2);

    boost::bind<int>(&printBind, boost::placeholders::_2, false, boost::placeholders::_1)(4.0, 1);
    boost::bind(&printBind,  boost::placeholders::_1, boost::placeholders::_1 ,boost::placeholders::_1)(1);
//    std::vector<int> v;
//
//    for(int i = 0; i < 10; i++)
//    {
//        v.push_back(i);
//    }
//
//    int res = std::count_if(v.begin(), v.end(), std::bind1st(std::less<int>(), 5));
//    auto a = std::bind1st(std::less<int>(), 5)(52);
//    std::cout << "the res: " << a << std::endl;

    boost::function<void(int)> f = std::cout << "_1: " << boost::lambda::_1;
    f(1314);

    auto f2 = boost::lambda::_1 + boost::lambda::_2;
    std::cout << "f2(x,y) = " << f2(20, 36);
    return 0;
}
