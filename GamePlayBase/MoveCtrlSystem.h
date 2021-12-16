#ifndef _GAMEPLAYER_MOVE_CTRL_SYSTEM_H_
#define _GAMEPLAYER_MOVE_CTRL_SYSTEM_H_

#include "SystemBase.h"
#include "GamePlayECSConfig.h"

class MoveCtrlSystem : public SystemBase<MoveCtrlComponent>
{
public:
    MoveCtrlSystem();
    virtual ~MoveCtrlSystem();

private:
    bool Update(MoveCtrlComponent* pComponent);

};

#endif