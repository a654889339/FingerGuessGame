#ifndef _GAMESERVER_MOVE_SYSTEM_H_
#define _GAMESERVER_MOVE_SYSTEM_H_

#include "SystemBase.h"

class MoveSystem : SystemBase
{
public:
    MoveSystem();
    virtual ~MoveSystem();

    void Update(int nUpdateTime);

private:

};

#endif