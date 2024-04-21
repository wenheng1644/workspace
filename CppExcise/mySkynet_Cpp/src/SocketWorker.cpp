//
// Created by ADMIN on 24-4-21.
//

#include "SocketWorker.h"

#include "iostream"
#include "thread"

void SocketWorker::init()
{
    std::cout << "SocketWorker init" << std::endl;
}

void SocketWorker::operator()()
{
    std::cout << "SokcetWorker loop" << std::endl;

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}