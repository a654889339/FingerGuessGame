#include "stdafx.h"
#include "PlayerManager.h"
//
//void PLAYER_STATE_WAITING::Enter(GameState eState, Player* pPlayer)
//{
//    JYLOG_PROCESS_ERROR(pPlayer);
//
//    JY_STD_VOID_END
//}
//
//void PLAYER_STATE_WAITING::Leave(GameState eState, Player* pPlayer)
//{
//    JYLOG_PROCESS_ERROR(pPlayer);
//
//    JY_STD_VOID_END
//}
//
//void PLAYER_STATE_PLAYING::Enter(GameState eState, Player* pPlayer)
//{
//    JYLOG_PROCESS_ERROR(pPlayer);
//
//    JY_STD_VOID_END
//}
//
//void PLAYER_STATE_PLAYING::Leave(GameState eState, Player* pPlayer)
//{
//    JYLOG_PROCESS_ERROR(pPlayer);
//
//    JY_STD_VOID_END
//}

PlayerManager::PlayerManager()
{
    //m_PlayerState[egame_state_waiting] = (PLAYER_STATE_TRIGGER*)&m_PlayerStateWaiting;
    //m_PlayerState[egame_state_playing] = (PLAYER_STATE_TRIGGER*)&m_PlayerStatePlaying;
}

PlayerManager::~PlayerManager()
{

}

bool PlayerManager::Init()
{
    bool bResult = false;

    JY_STD_BOOL_END
}

void PlayerManager::UnInit()
{
    m_PlayerMap.clear();
}

// Add or Remove
bool PlayerManager::AddPlayer(int32 dwPlayerID, const char szName[])
{
    bool bResult = false;
    bool bRetCode = false;
    Player* pPlayer = NULL;
    bool bAddNameFlag = false;
    bool bAddPlayerFlag = false;

    bRetCode = m_NameManager.add(STString(szName), dwPlayerID);
    JYLOG_PROCESS_ERROR(bRetCode);
    bAddNameFlag = true;

    pPlayer = m_PlayerMap.add(dwPlayerID);
    JYLOG_PROCESS_ERROR(pPlayer);
    bAddPlayerFlag = true;

    printf("[PlayerManager] Player %s, ID:%u, Login.\n", szName, dwPlayerID);

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bAddNameFlag)
        {
            bAddNameFlag = false;
            m_NameManager.remove(szName);
        }

        if (bAddPlayerFlag)
        {
            bAddPlayerFlag = false;
            m_PlayerMap.remove(dwPlayerID);
        }
    }
    return bResult;
}

void PlayerManager::RemovePlayer(int32 dwPlayerID)
{
    bool bRetCode = false;
    Player* pPlayer = NULL;

    pPlayer = GetPlayer(dwPlayerID);
    JYLOG_PROCESS_ERROR(pPlayer);

    bRetCode = m_NameManager.remove(STString(pPlayer->m_szName));
    JYLOG_PROCESS_ERROR(bRetCode);

    printf("[PlayerManager] Player %s Logout.\n", pPlayer->m_szName);

    bRetCode = m_PlayerMap.remove(pPlayer->m_dwPlayerID);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_VOID_END
}

// Modify
// Query
bool PlayerManager::IsOnline(const char szName[])
{
    return m_NameManager.find(STString(szName)) != NULL;
}

Player* PlayerManager::GetPlayer(int32 dwPlayerID)
{
    return m_PlayerMap.find(dwPlayerID);
}

Player* PlayerManager::GetPlayer(const char szName[])
{
    Player* pResult = NULL;
    int32* pdwPlayerID = NULL;

    pdwPlayerID = m_NameManager.find(STString(szName));
    JY_PROCESS_ERROR(pdwPlayerID);

    pResult = GetPlayer(*pdwPlayerID);
Exit0:
    return pResult;
}
