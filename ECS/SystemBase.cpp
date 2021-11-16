#include "stdafx.h"
#include "SystemBase.h"

SystemBase::SystemBase()
{
    m_bEnable        = true;
    m_pComponentList = NULL;

    memset(m_ProcessUpdateFuns, 0, sizeof(m_ProcessUpdateFuns));
}

bool SystemBase::RegisterUpdatePriorLevel(uint8_t uPriorLevel, PROCESS_UPDATE_FUNC Func)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(uPriorLevel < ECS_SYSTEM_UPDATE_FUNC_COUNT);
    JYLOG_PROCESS_ERROR(!m_ProcessUpdateFuns[uPriorLevel]);

    m_ProcessUpdateFuns[uPriorLevel] = Func;

    JY_STD_BOOL_END
}

bool SystemBase::NeedUpdate(uint8_t uPriorLevel)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(uPriorLevel < ECS_SYSTEM_UPDATE_FUNC_COUNT);
    JY_PROCESS_ERROR(m_ProcessUpdateFuns[uPriorLevel]);

    JY_STD_BOOL_END
}

bool SystemBase::Update(uint8_t uPriorLevel)
{
    bool                bResult    = false;
    void*               pComponent = NULL;
    PROCESS_UPDATE_FUNC Func;

    JYLOG_PROCESS_ERROR(uPriorLevel < ECS_SYSTEM_UPDATE_FUNC_COUNT);
    JYLOG_PROCESS_ERROR(m_pComponentList);

    Func = m_ProcessUpdateFuns[uPriorLevel];
    JYLOG_PROCESS_ERROR(Func);

    m_pComponentList->BeginTraversal();

    while (true)
    {
        pComponent = m_pComponentList->TraversalNextComponent();
        JY_PROCESS_SUCCESS(!pComponent);

        (this->*Func)(pComponent);
    }

    JY_STD_BOOL_SUCCESS_END
}

bool SystemBase::SetComponentList(ComponentListBase* pComponentList)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(pComponentList);
    JYLOG_PROCESS_ERROR(!m_pComponentList);

    m_pComponentList = pComponentList;

    JY_STD_BOOL_END
}