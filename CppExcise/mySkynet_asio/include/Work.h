//
// Created by 文恒 on 24-10-6.
//

#ifndef WORK_H
#define WORK_H

#pragma once
#include "Sunnet.h"
#include <condition_variable>

#include "Service.h"

class Sunnet;

class Work
{
public:
  int m_id;
  int m_eachNum;
  Work();
  ~Work() = default;
  void operator()();
  void checkAndPushGlobal(std::shared_ptr<Service> srv);
};


#endif //WORK_H
