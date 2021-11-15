#ifndef _GAMESERVER_MOVE_SYSTEM_H_
#define _GAMESERVER_MOVE_SYSTEM_H_

#include "SystemBase.h"
#include "GamePlayECSConfig.h"

class MoveSystem : SystemBase
{
public:
    MoveSystem();
    virtual ~MoveSystem();

    void Update(int nUpdateTime);
    bool SetComponentList(MoveComponentList* pList);

private:
    MoveComponentList* m_pComponentList; // System没有数据，所以要另外设置一下 需要Update的数据块。

};

#endif