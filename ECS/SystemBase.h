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
    SystemBase();

    bool RegisterUpdatePriorLevel(uint8_t uPriorLevel, PROCESS_UPDATE_FUNC Func); // �����ʼ��ʱ��Ҫ ע����º���
    bool SetComponentList(ComponentManager* pComponentManager);

    virtual bool Update0(void* pComponent) {return true;};
    virtual bool Update1(void* pComponent) {return true;};
    virtual bool Update2(void* pComponent) {return true;};

private:
    bool NeedUpdate(uint8_t uPriorLevel); // �ж�������ȼ��ĸ��º����Ƿ�ע���
    bool Update(uint8_t uPriorLevel);

private:
    PROCESS_UPDATE_FUNC   m_ProcessUpdateFuns[ECS_SYSTEM_UPDATE_FUNC_COUNT];

    ComponentManager*     m_pComponentList;
};

#endif