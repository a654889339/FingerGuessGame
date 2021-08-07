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

    bool AddPlayer(int nConnIndex, const char szName[]);

private:
    typedef SplayTree<int,Player> PLAYER_MANAGER_MAP;
    PLAYER_MANAGER_MAP m_PlayerManager;
};

#endif