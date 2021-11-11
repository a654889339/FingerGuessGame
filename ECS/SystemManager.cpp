#include "stdafx.h"
#include "SystemManager.h"

SystemManager::SystemManager()
{
    m_nSystemSize = 0;
}

SystemManager::~SystemManager()
{

}

bool SystemManager::Init(int nSystemTotalSize)
{
    bool bResult = false;

    m_SystemList.resize(nSystemTotalSize);
    m_nSystemSize = nSystemTotalSize;

    JY_STD_BOOL_END
}

void SystemManager::UnInit()
{

}

void SystemManager::Active()
{
    UpdateAll();
}

void SystemManager::UpdateAll()
{
    for (int i = 0; i < m_nSystemSize; i++)
    {

    }
}
