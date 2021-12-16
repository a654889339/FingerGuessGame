#ifndef _ECS_COMPONENT_LIST_H_
#define _ECS_COMPONENT_LIST_H_

#include "ECSDef.h"

#include <vector>

template <typename Component>
class ComponentList
{
    //template<class _Child, class ... Args>
    //_Child* const Create(Args ... args) const
    //{
    //    auto& child = new _Child(this, args ...);
    //    this->children_.emplace_back(child);
    //    return child;
    //}
public:
    int_eid Add(Component* pComponent);
    bool    Del(int_eid nID);

    Component* Create(int_eid& nID);
    Component* Get(int_eid nID);

    void TraversalInit()
    {
        m_Manager.traversal_init();
    }

    template <class TraversalFunc>
    bool TraversalNextComponent(TraversalFunc Func)
    {
        bool bResult  = false;
        bool bRetCode = false;

        bRetCode = m_Manager.traversal<TraversalFunc>(Func);
        JY_PROCESS_ERROR(bRetCode);

        JY_STD_BOOL_END
    }

    Component* TraversalGetNext()
    {
        return NULL;
    }

private:
    JYVector<Component, int_eid> m_Manager;
};

#endif