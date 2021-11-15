#include "ComponentList.h"

template <typename Component>
int_eid ComponentList<Component>::Add(Component* pComponent)
{
    return m_Manager.add(pComponent);
}

template <typename Component>
bool ComponentList<Component>::Del(int_eid nID)
{
    return m_Manager.del(nID);
}


template <typename Component>
Component* ComponentList<Component>::Create(int_eid& nID)
{
    return m_Manager.create(nID);
}

template <typename Component>
Component* ComponentList<Component>::Get(int_eid nID)
{
    return m_Manager.get(nID);
}