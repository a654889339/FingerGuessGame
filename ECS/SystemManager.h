#ifndef _ECS_SYSTEM_MANAGER_H_
#define _ECS_SYSTEM_MANAGER_H_

#include "SystemObj.h"

#include <vector>

class SystemManager
{
public:
    SystemManager();
    virtual ~SystemManager();

    bool Init();
    void UnInit();

    void Active();

    bool AddSystem(SystemObj* pSystem);

private:
    void UpdateAll();

    std::vector<SystemObj*> m_SystemList;
};

#endif