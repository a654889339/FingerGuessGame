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

template <typename Component>
void* ComponentList<Component>::TrasverNextComponent()
{
    void* pResult = NULL;

    JY_PROCESS_ERROR(m_nTrasverIndex < m_Manager.size());

    pResult = &m_Manager[m_nTrasverIndex++];
Exit0:
    return pResult;
}