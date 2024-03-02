#ifndef MULARGTEMPLATE
#define MULARGTEMPLATE

#include "iostream"

void print()
{

}

template<typename T, typename... Arg>
void print(T first, Arg... args)
{
    std::cout << "first: " << first << std::endl;;

    std::cout << "leftArg num = " << sizeof...(args) << std::endl;

    if(sizeof...(args) > 0)
    {
        print(args...);
    }
    else
    {
        std::cout << "sizeof... num = 0" << std::endl;
    }

}

#endif