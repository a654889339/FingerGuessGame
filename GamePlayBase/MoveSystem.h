#ifndef _GAMEPLAYER_MOVE_SYSTEM_H_
#define _GAMEPLAYER_MOVE_SYSTEM_H_

#include "SystemBase.h"
#include "GamePlayECSConfig.h"

class MoveSystem : public SystemBase<MoveComponent>
{
public:
    MoveSystem();
    virtual ~MoveSystem();

private:
    bool Update0(MoveComponent* pComponent);

};

#endif