#ifndef _GAMESERVER_MOVE_SYSTEM_H_
#define _GAMESERVER_MOVE_SYSTEM_H_

#include "SystemBase.h"
#include "GamePlayECSConfig.h"

class MoveSystem : SystemBase<MoveComponent>
{
public:
    MoveSystem();
    virtual ~MoveSystem();

private:
};

#endif