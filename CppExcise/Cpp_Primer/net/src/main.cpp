
/*
    测试文件

*/

#include "net.h"

int main()
{
    my_net::tcp obj("127.0.0.1", 8888);
    obj.start(); 
    return 0;
}