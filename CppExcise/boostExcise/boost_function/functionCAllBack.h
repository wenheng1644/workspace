//
// Created by wenheng on 2022/3/27.
//

#ifndef BOOST_FUNCTION_FUNCTIONCALLBACK_H
#define BOOST_FUNCTION_FUNCTIONCALLBACK_H

#include <iostream>
class functionCAllBack;

typedef bool (*normal_fp)(int);

class functionCAllBack {
public:
    functionCAllBack(normal_fp fp) : m_fp(fp) {}

    void calc(int v1, int v2)
    {
        std::cout << "v1 + v2 = " << v1 + v2 << std::endl;
    }

    void callback(int v)
    {
        m_fp(v);
    }
private:
    normal_fp m_fp;
};


#endif //BOOST_FUNCTION_FUNCTIONCALLBACK_H
