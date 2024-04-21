//
// Created by ADMIN on 24-4-16.
//

#ifndef SUNNET_WORKER_H
#define SUNNET_WORKER_H
#pragma once

#include "thread"

#include "Service.h"
#include "Sunnet.h"

class Sunnet;


class Worker
{
public:
    int id;
    int eachNum;
    void operator()();
    void CheckAndPutGloabl(std::shared_ptr<Service> svr);
};


#endif //SUNNET_WORKER_H
