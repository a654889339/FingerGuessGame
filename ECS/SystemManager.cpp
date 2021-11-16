#include "stdafx.h"
#include "SystemManager.h"

SystemManager::SystemManager()
{
}

SystemManager::~SystemManager()
{

}

bool SystemManager::Init()
{
    bool bResult = false;

    JY_STD_BOOL_END
}

void SystemManager::UnInit()
{

}

void SystemManager::Active()
{
    UpdateAll();
}

bool SystemManager::AddSystem(SystemObj* pSystem)
{
    for (int i = 0; i < ECS_SYSTEM_UPDATE_FUNC_COUNT; i++)
        if (pSystem->NeedUpdate(i))
            m_SystemList[i].push_back(pSystem);
}

//////////////////////////////////////////////////////////////////////////

void SystemManager::UpdateAll()
{
    for (uint8_t uPriorLevel = 0; uPriorLevel < ECS_SYSTEM_UPDATE_FUNC_COUNT; uPriorLevel++)
    {
        for (int j = 0; j < m_SystemList[uPriorLevel].size(); j++)
        {
            SystemObj* pSystem = m_SystemList[uPriorLevel][j];

            JYLOG_PROCESS_ERROR(pSystem);
            JY_TRUE_CONTINUE(!pSystem->IsEnable());

            pSystem->Update(uPriorLevel);
        }
    }

    JY_STD_VOID_END
}