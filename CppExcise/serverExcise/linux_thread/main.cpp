//
// Created by wenheng on 2022/4/23.
//

#include "pthread.h"
#include "thread"
#include "sys/socket.h"
#include "iostream"
void hello(void* args)
{
    while(true)
    {
        std::cout << "hello world" << std::endl;
    }


}

int main()
{
//    pthread_t pid;
//    pthread_create(&pid, NULL, &hello, NULL);

    std::thread t1(&hello, nullptr);
    while(true)
    {

    }
    return 0;
}