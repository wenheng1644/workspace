#ifndef GATEMANAGER
#define GATEMANAGER

#include "gate_comm.h"
#include "../logic/GateUserEng.h"

//网关管理器
class GateManager : public Singleton<GateManager>
{
public:
    GateManager() = default;

    void init();

    ioserver_tp& clientIO() { return m_clientWork.get_io();}
    ioserver_tp& serverIO() { return m_serverWork.get_io();}

    GateUserEng m_userEng;

    void run();

private:
    WorkRunner m_clientWork;    //客户端任务循环事件
    WorkRunner m_serverWork;    //逻辑服循环事件
    WorkRunner m_userWork;
    void init_WorkRunner();
};


#endif