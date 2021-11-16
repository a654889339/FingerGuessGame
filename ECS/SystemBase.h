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

    bool RegisterUpdatePriorLevel(uint8_t uPriorLevel, PROCESS_UPDATE_FUNC Func); // �����ʼ��ʱ��Ҫ ע����º���
    bool NeedUpdate(uint8_t uPriorLevel); // �ж�������ȼ��ĸ��º����Ƿ�ע���
    bool Update(uint8_t uPriorLevel);

    bool SetComponentList(ComponentListBase* pComponentList);

    bool IsEnable() { return m_bEnable; }
    void Enable()   { m_bEnable = true; }
    void Disable()  { m_bEnable = false; }

protected:
    bool    m_bEnable;     // ϵͳ����

private:
    PROCESS_UPDATE_FUNC   m_ProcessUpdateFuns[ECS_SYSTEM_UPDATE_FUNC_COUNT];

    ComponentListBase*    m_pComponentList;
};

#endif