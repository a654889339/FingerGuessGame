#ifndef _ECS_SYSTEM_BASE_H_
#define _ECS_SYSTEM_BASE_H_

#include "ComponentList.h"
#include "SystemObj.h"

template <typename Component>
class SystemBase : public SystemObj
{
private:
    typedef void (SystemBase::* PROCESS_UPDATE_FUNC)(void* pComponent);
    typedef ComponentList<Component> ComponentManager;

public:
    SystemBase();

    bool RegisterUpdatePriorLevel(uint8_t uPriorLevel, PROCESS_UPDATE_FUNC Func); // 程序初始化时需要 注册更新函数
    bool SetComponentList(ComponentManager* pComponentManager);

private:
    bool NeedUpdate(uint8_t uPriorLevel); // 判断这个优先级的更新函数是否注册过
    bool Update(uint8_t uPriorLevel);

private:
    PROCESS_UPDATE_FUNC   m_ProcessUpdateFuns[ECS_SYSTEM_UPDATE_FUNC_COUNT];

    ComponentManager*     m_pComponentList;
};

#endif