#ifndef _ECS_SYSTEM_BASE_H_
#define _ECS_SYSTEM_BASE_H_

#include "ComponentList.h"
#include "SystemObj.h"

template <typename Component>
class SystemBase : public SystemObj
{
private:
    typedef ComponentList<Component> ComponentManager;

public:
    SystemBase()
    {
        m_pComponentList = NULL;
    }

    virtual void Active()
    {
        Component* pComponent = NULL;

        m_pComponentList->TraversalInit();

        do 
        {
            pComponent = m_pComponentList->TraversalGetNext();
            JY_PROCESS_ERROR(pComponent);

            Update(pComponent);
        }
        while (true);

        JY_STD_VOID_END
    }

    bool SetComponentList(ComponentManager* pComponentManager)
    {
        bool bResult = false;

        JYLOG_PROCESS_ERROR(pComponentManager);
        JYLOG_PROCESS_ERROR(!m_pComponentList);

        m_pComponentList = pComponentManager;

        JY_STD_BOOL_END
    }

    virtual bool Update(Component* pComponent) = 0;

private:
    bool operator()(Component* pComponent)
    {
        return Update(pComponent);
    }

private:
    ComponentManager*     m_pComponentList;
};

#endif