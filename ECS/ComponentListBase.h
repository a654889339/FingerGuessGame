#ifndef _ECS_COMPONENT_LIST_BASE_H_
#define _ECS_COMPONENT_LIST_BASE_H_

class ComponentListBase
{
    ComponentListBase()   { m_nTrasverIndex = 0; }
    void ResetTrasver()   { m_nTrasverIndex = 0; }
    virtual void* TrasverNextComponent() = 0;

protected:
    size_t  m_nTrasverIndex;
};

#endif