#include "GateManager.h"

void GateManager::init()
{
    init_WorkRunner();
}

void GateManager::run()
{
    m_clientWork.post(std::bind(&GateUserEng::run, &m_userEng));
}

void GateManager::init_WorkRunner()
{
    m_clientWork.start(1);
    m_serverWork.start(1);
}