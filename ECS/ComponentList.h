#ifndef _ECS_COMPONENT_LIS T_H_
#define _ECS_COMPONENT_LIST_H_

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
    int_eid Add(Component* pComponent)
    {
        int_eid nResult = ERROR_EID;

        JYLOG_PROCESS_ERROR(pComponent);




        nResult = true;
    Exit0:
        return nResult;
    }

    Component* GetNewOne()
    {

    }

private:
    std::vector<Component> m_Manager;
    std::vector<int_eid>   m_EnableFlag; // Enable = 0; Disenable = Next enable Component in m_Manager's index, last disenable = -1.
    std::queue<int_eid>    m_UnuseID;
};

#endif