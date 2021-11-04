#ifndef _BASE_JYVECTOR_H_
#define _BASE_JYVECTOR_H_

#define JYVECTOR_ERROR_INDEX -1

template <typename T, typename ID_TYPE>
class JYVector
{
    std::vector<Component>          m_Manager;
    std::vector<ID_TYPE>            m_NextEnableIndex; // Enable = 0; Disenable = Next enable Component in m_Manager's index, last disenable = -1.
    std::vector<ID_TYPE>            m_PreEnableIndex;
    std::priority_queue<ID_TYPE>    m_UnuseID;

};


#endif