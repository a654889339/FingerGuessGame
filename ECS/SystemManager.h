#ifndef _ECS_SYSTEM_MANAGER_H_
#define _ECS_SYSTEM_MANAGER_H_

#include "SystemBase.h"

#include <vector>

class SystemManager
{
public:
    SystemManager();
    virtual ~SystemManager();

    bool Init(int nSystemTotalSize);
    void UnInit();

    void Active();

private:
    void UpdateAll();

    std::vector<SystemBase> m_SystemList;
    int                     m_nSystemSize;

};

#endif