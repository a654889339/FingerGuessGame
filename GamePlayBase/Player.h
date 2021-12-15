#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "stdafx.h"
#include "PlayerConfig.h"

class Player
{
public:
    Player()
    {
        m_dwPlayerID = ERROR_ID;
        memset(m_szName, 0, sizeof(m_szName));
    }

#ifdef _SERVER
    bool Init(int32 dwPlayerID, int nConnIndex, const char szName[])
    {
        bool bResult = false;

        m_dwPlayerID = dwPlayerID;

        strncpy(m_szName, szName, sizeof(m_szName));
        m_szName[sizeof(m_szName) - 1] = '\0';

        JY_STD_BOOL_END
    }

#endif
    void UnInit();

public:
    int32 m_dwPlayerID;
    char m_szName[_NAME_LEN];
};

class PLAYER_STATE_TRIGGER
{
public:
    virtual void Enter(GameState eState, Player* pPlayer) {};
    virtual void Leave(GameState eState, Player* pPlayer) {};

    GameState m_eState;
};

//class PLAYER_STATE_MANAGER
//{
//public:
//    PLAYER_STATE_MANAGER()
//    {
//        for (int i = egame_state_begin; i < egame_state_end; i++)
//        {
//            m_PlayerState[i] = &m_PlayerStateConst[i];
//            m_PlayerStateConst[i].m_eState = (GameState)i;
//        }
//    }
//
//    bool SetPlayerState(Player* pPlayer, GameState eState)
//    {
//        bool bResult = false;
//        PLAYER_STATE_TRIGGER* pTrigger = NULL;
//
//        JY_PROCESS_ERROR(pPlayer);
//        JYLOG_PROCESS_ERROR(eState >= egame_state_begin && eState < egame_state_end);
//        JYLOG_PROCESS_ERROR(pPlayer->m_eState >= egame_state_begin && pPlayer->m_eState < egame_state_end);
//
//        pTrigger = m_PlayerState[pPlayer->m_eState];
//        JYLOG_PROCESS_ERROR(pTrigger);
//
//        pTrigger->Leave(eState, pPlayer);
//
//        pTrigger = m_PlayerState[eState];
//        JYLOG_PROCESS_ERROR(pTrigger);
//
//        pTrigger->Enter(pPlayer->m_eState, pPlayer);
//        pPlayer->m_eState = eState;
//
//        JY_STD_BOOL_END
//    }
//
//public:
//    PLAYER_STATE_TRIGGER* m_PlayerState[egame_state_end];
//
//private:
//    PLAYER_STATE_TRIGGER m_PlayerStateConst[egame_state_end];
//};
#endif