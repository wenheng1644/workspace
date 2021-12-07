/**
 * @file temFunc.h
 * @author xwz
 * @brief 模板函数头文件
 * @version 0.1
 * @date 2021-11-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef TEMFUNC
#define TEMFUNC
#include <iostream>
template <typename T>
int compare(const T& v1,const T& v2){
    if(v1 < v2) return -1;
    if(v2 < v1) return 1;

    return 0;
}

template <typename iter,typename T>
iter find_temp(iter TheBegin,iter TheEnd,T val)
{
    if(TheBegin == TheEnd) return TheEnd;

    while(TheBegin != TheEnd)
    {
        if(*TheBegin == val)
            break;

        TheBegin++;
    }
    return TheBegin;
}

template <typename T>
void print_temp(const T& arr)
{
    for(const auto e : arr)
        std::cout << e << " ";
    std::cout << std::endl;
}

#endif