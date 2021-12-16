#ifndef _GAME_PLAYER_H_
#define _GAME_PLAYER_H_

// ECS
#include "SystemManager.h"
#include "MoveCtrlSystem.h"
#include "MoveSystem.h"

// Config
#include "GamePlayECSConfig.h"

class GamePlay
{
public:
    GamePlay();
    virtual ~GamePlay();

    bool Init();
    void UnInit();

    void Active();

public:
    SystemManager         m_SystemManager;

private:
    // Component
    MoveComponentList     m_MoveCList;
    MoveCtrlComponentList m_MoveCtrlCList;

    // System
    MoveCtrlSystem        m_MoveCtrlSystem;
    MoveSystem            m_MoveSystem;
};

#endif