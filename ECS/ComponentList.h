#ifndef _ECS_COMPONENT_LIS T_H_
#define _ECS_COMPONENT_LIST_H_

#include "ECSDef.h"
#include "ComponentListBase.h"

#include <vector>

template <typename Component>
class ComponentList : ComponentListBase
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

    void* TrasverNextComponent();

private:
    JYVector<Component, int_eid> m_Manager;
};

#endif