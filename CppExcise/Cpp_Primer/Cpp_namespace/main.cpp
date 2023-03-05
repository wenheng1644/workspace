//
// Created by 文恒 on 2022/1/24.
//
#include "iostream"

using namespace std;

namespace mynsp
{
    int i = 0;
    double d = 0;
    const int limit = 1000;
}

int i = 0;

//using namespace mynsp;
using mynsp::i;
using mynsp::d;
using mynsp::limit;
int main()
{
//    using namespace mynsp;

//    using mynsp::i;
//    using mynsp::d;
//    using mynsp::limit;
    double j = 3.14;
    int iobj = limit + 1;
    ++i;
    ++::i;
    return 0;
}