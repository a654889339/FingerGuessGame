#include "stdafx.h"
#include "SystemBase.h"

template <typename Component>
SystemBase<Component>::SystemBase()
{
    m_bEnable        = true;
    m_pComponentList = NULL;

    memset(m_ProcessUpdateFuns, 0, sizeof(m_ProcessUpdateFuns));
}

template <typename Component>
bool SystemBase<Component>::RegisterUpdatePriorLevel(uint8_t uPriorLevel, PROCESS_UPDATE_FUNC Func)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(uPriorLevel < ECS_SYSTEM_UPDATE_FUNC_COUNT);
    JYLOG_PROCESS_ERROR(!m_ProcessUpdateFuns[uPriorLevel]);

    m_ProcessUpdateFuns[uPriorLevel] = Func;

    JY_STD_BOOL_END
}

template <typename Component>
bool SystemBase<Component>::SetComponentList(ComponentManager* pComponentList)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(pComponentList);
    JYLOG_PROCESS_ERROR(!m_pComponentList);

    m_pComponentList = pComponentList;

    JY_STD_BOOL_END
}

//////////////////////////////////////////////////////////////////////////

template <typename Component>
bool SystemBase<Component>::NeedUpdate(uint8_t uPriorLevel)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(uPriorLevel < ECS_SYSTEM_UPDATE_FUNC_COUNT);
    JY_PROCESS_ERROR(m_ProcessUpdateFuns[uPriorLevel]);

    JY_STD_BOOL_END
}

template <typename Component>
bool SystemBase<Component>::Update(uint8_t uPriorLevel)
{
    bool                bResult  = false;
    bool                bRetCode = false;
    PROCESS_UPDATE_FUNC Func;

    JYLOG_PROCESS_ERROR(uPriorLevel < ECS_SYSTEM_UPDATE_FUNC_COUNT);
    JYLOG_PROCESS_ERROR(m_pComponentList);

    Func = m_ProcessUpdateFuns[uPriorLevel];
    JYLOG_PROCESS_ERROR(Func);

    bRetCode = m_pComponentList->TraversalNextComponent(Func);
    JY_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_SUCCESS_END
}
