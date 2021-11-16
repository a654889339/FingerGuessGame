#ifndef _ECS_COMPONENT_LIST_BASE_H_
#define _ECS_COMPONENT_LIST_BASE_H_

class ComponentListBase
{
public:
    ComponentListBase()   { m_nTrasverIndex = 0; }
    void BeginTraversal()   { m_nTrasverIndex = 0; }
    virtual void* TraversalNextComponent() = 0;

protected:
    size_t  m_nTrasverIndex;
};

#endif