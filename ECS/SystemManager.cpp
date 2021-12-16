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
    bool bResult = false;

    m_SystemList.push_back(pSystem);

    JY_STD_BOOL_END
}

//////////////////////////////////////////////////////////////////////////

void SystemManager::UpdateAll()
{
    for (int j = 0; j < m_SystemList.size(); j++)
    {
        SystemObj* pSystem = m_SystemList[j];

        JYLOG_PROCESS_ERROR(pSystem);
        JY_TRUE_CONTINUE(!pSystem->IsEnable());

        pSystem->Active();
    }

    JY_STD_VOID_END
}