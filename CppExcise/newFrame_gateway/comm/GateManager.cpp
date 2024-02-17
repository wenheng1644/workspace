#include "GateManager.h"

void GateManager::init()
{
    init_WorkRunner();
}

void GateManager::init_WorkRunner()
{
    m_clientWork.start(1);
    m_serverWork.start(1);
}