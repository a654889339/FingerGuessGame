#ifndef _ECS_SYSTEM_BASE_H_
#define _ECS_SYSTEM_BASE_H_

#include "ComponentListBase.h"

#define ECS_SYSTEM_UPDATE_FUNC_COUNT 3

class SystemBase
{
private:
    typedef void (SystemBase::* PROCESS_UPDATE_FUNC)(void* pComponent);

public:
    SystemBase();

    bool RegisterUpdatePriorLevel(uint8_t uPriorLevel, PROCESS_UPDATE_FUNC Func); // 程序初始化时需要 注册更新函数
    bool NeedUpdate(uint8_t uPriorLevel); // 判断这个优先级的更新函数是否注册过
    bool Update(uint8_t uPriorLevel);

    bool SetComponentList(ComponentListBase* pComponentList);

    bool IsEnable() { return m_bEnable; }
    void Enable()   { m_bEnable = true; }
    void Disable()  { m_bEnable = false; }

protected:
    bool    m_bEnable;     // 系统开关

private:
    PROCESS_UPDATE_FUNC   m_ProcessUpdateFuns[ECS_SYSTEM_UPDATE_FUNC_COUNT];

    ComponentListBase*    m_pComponentList;
};

#endif