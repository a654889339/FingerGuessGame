#ifndef _PLAYER_MANAGER_H_
#define _PLAYER_MANAGER_H_

#include "Player.h"

class PlayerManager
{
public:
    PlayerManager();
    virtual ~PlayerManager();

    bool Init();
    void UnInit();

private:


};

#endif