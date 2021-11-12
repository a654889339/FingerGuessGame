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

bool SystemManager::AddSystem(SystemBase* pSystem)
{
    for (int i = 0; i < ECS_SYSTEM_UPDATE_FUNC_COUNT; i++)
        if (pSystem->IsUpdateTime(i))
            m_SystemList[i].push_back(pSystem);
}

void SystemManager::UpdateAll()
{
    for (int i = 0; i < ECS_SYSTEM_UPDATE_FUNC_COUNT; i++)
    {
        for (int j = 0; j < m_SystemList[i].size(); j++)
        {
            SystemBase* pSystem = m_SystemList[i][j];

            JYLOG_PROCESS_ERROR(pSystem);
            JY_TRUE_CONTINUE(!pSystem->IsEnable());

            pSystem->Update(i);
        }
    }

    JY_STD_VOID_END
}