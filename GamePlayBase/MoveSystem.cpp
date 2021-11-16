#include "stdafx.h"
#include "MoveSystem.h"

MoveSystem::MoveSystem()
{
    m_bEnable        = true;
    m_pComponentList = NULL;
}

MoveSystem::~MoveSystem()
{

}

void MoveSystem::Update(int nUpdateTime)
{
    JYLOG_PROCESS_ERROR(m_pComponentList);

    JY_STD_VOID_END
}

bool MoveSystem::SetComponentList(MoveComponentList* pList)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(pList);
    JYLOG_PROCESS_ERROR(!m_pComponentList);

    m_pComponentList = pList;

    JY_STD_BOOL_END
}