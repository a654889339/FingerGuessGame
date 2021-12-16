#include "stdafx.h"
#include "GamePlay.h"

#define REGISTER_SYSTEM(Sys) m_SystemManager.AddSystem((SystemObj*)&Sys)
#define REGISTER_SYSTEM_COMPONENT(Sys, CList) Sys.SetComponentList(&CList)

GamePlay::GamePlay()
{

}
GamePlay::~GamePlay()
{

}

bool GamePlay::Init()
{
    bool bResult = false;

    REGISTER_SYSTEM(m_MoveCtrlSystem);
    REGISTER_SYSTEM(m_MoveSystem);

 /*   REGISTER_SYSTEM_COMPONENT(m_MoveCtrlSystem, m_MoveCtrlCList);
    REGISTER_SYSTEM_COMPONENT(m_MoveSystem,     m_MoveCList);*/


    JY_STD_BOOL_END
}

void GamePlay::UnInit()
{

}

void GamePlay::Active()
{
    m_SystemManager.Active();
}