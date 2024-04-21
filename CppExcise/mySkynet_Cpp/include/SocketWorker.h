//
// Created by ADMIN on 24-4-21.
//

#ifndef SUNNET_SOCKETWORKER_H
#define SUNNET_SOCKETWORKER_H

#pragma once

class SocketWorker
{
public:
    SocketWorker() = default;
    void init();

    void operator()();
};

#endif //SUNNET_SOCKETWORKER_H
