#ifndef _ECS_SYSTEM_BASE_H_
#define _ECS_SYSTEM_BASE_H_

#include "ComponentList.h"
#include "SystemObj.h"

template <typename Component>
class SystemBase : public SystemObj
{
private:
    typedef bool (SystemBase::* PROCESS_UPDATE_FUNC)(void* pComponent);
    typedef ComponentList<Component> ComponentManager;

public:
    SystemBase()
    {
        m_bEnable = true;
        m_pComponentList = NULL;

        memset(m_ProcessUpdateFuns, 0, sizeof(m_ProcessUpdateFuns));
        RegisterUpdatePriorLevel(0, &SystemBase::Update0);
    }

    bool RegisterUpdatePriorLevel(uint8_t uPriorLevel, PROCESS_UPDATE_FUNC Func) // 程序初始化时需要 注册更新函数
    {
        bool bResult = false;

        JYLOG_PROCESS_ERROR(uPriorLevel < ECS_SYSTEM_UPDATE_FUNC_COUNT);
        JYLOG_PROCESS_ERROR(!m_ProcessUpdateFuns[uPriorLevel]);

        m_ProcessUpdateFuns[uPriorLevel] = Func;

        JY_STD_BOOL_END
    }

    bool SetComponentList(ComponentManager* pComponentManager)
    {
        bool bResult = false;

        JYLOG_PROCESS_ERROR(pComponentManager);
        JYLOG_PROCESS_ERROR(!m_pComponentList);

        m_pComponentList = pComponentManager;

        JY_STD_BOOL_END
    }

    virtual bool Update0(void* pComponent) {return true;};
    virtual bool Update1(void* pComponent) {return true;};
    virtual bool Update2(void* pComponent) {return true;};

private:
    bool NeedUpdate(uint8_t uPriorLevel) // 判断这个优先级的更新函数是否注册过
    {
        bool bResult = false;

        JYLOG_PROCESS_ERROR(uPriorLevel < ECS_SYSTEM_UPDATE_FUNC_COUNT);
        JY_PROCESS_ERROR(m_ProcessUpdateFuns[uPriorLevel]);

        JY_STD_BOOL_END
    }

    bool Update(uint8_t uPriorLevel)
    {
        bool                bResult = false;
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

private:
    PROCESS_UPDATE_FUNC   m_ProcessUpdateFuns[ECS_SYSTEM_UPDATE_FUNC_COUNT];

    ComponentManager*     m_pComponentList;
};

#endif