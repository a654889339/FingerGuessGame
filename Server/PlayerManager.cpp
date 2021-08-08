#include "stdafx.h"
#include "PlayerManager.h"
#include "ServerWorld.h"

void PLAYER_STATE_WAITING::Enter(GameState eState, Player* pPlayer)
{
    JYLOG_PROCESS_ERROR(pPlayer);

    JY_STD_VOID_END
}

void PLAYER_STATE_WAITING::Leave(GameState eState, Player* pPlayer)
{
    JYLOG_PROCESS_ERROR(pPlayer);

    JY_STD_VOID_END
}

PlayerManager::PlayerManager()
{
    m_PlayerState[egame_state_waiting] = (PLAYER_STATE_TRIGGER*)&m_PlayerStateWaiting;
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
    m_PlayerManager.Clear();
}

// Add or Remove
bool PlayerManager::AddPlayer(int nConnIndex, const char szName[])
{
    bool bResult = false;
    bool bRetCode = false;
    DWORD dwPlayerID = ERROR_ID;
    Player* pPlayer = NULL;
    bool bAddNameFlag = false;
    bool bAddConnIndexFlag = false;
    bool bAddPlayerFlag = false;

    dwPlayerID = g_pServer->m_DB.LoadPlayerIDByName(szName);
    JYLOG_PROCESS_ERROR(dwPlayerID != ERROR_ID);

    bRetCode = m_NameManager.Add(STString(szName), dwPlayerID);
    JYLOG_PROCESS_ERROR(bRetCode);
    bAddNameFlag = true;

    bRetCode = m_ConnIndexManager.Add(nConnIndex, dwPlayerID);
    JYLOG_PROCESS_ERROR(bRetCode);
    bAddConnIndexFlag = true;

    pPlayer = m_PlayerManager.Add(dwPlayerID);
    JYLOG_PROCESS_ERROR(pPlayer);
    bAddPlayerFlag = true;

    bRetCode = pPlayer->Init(dwPlayerID, nConnIndex, szName);
    JYLOG_PROCESS_ERROR(bRetCode);

    bRetCode = g_pServer->m_DB.LoadPlayer(pPlayer);
    JYLOG_PROCESS_ERROR(bRetCode);

    printf("[PlayerManager] Player %s, ID:%u, ConnIndex:%d Login.\n", szName, dwPlayerID, nConnIndex);

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bAddNameFlag)
        {
            bAddNameFlag = false;
            m_NameManager.Remove(szName);
        }

        if (bAddConnIndexFlag)
        {
            bAddConnIndexFlag = false;
            m_ConnIndexManager.Remove(nConnIndex);
        }

        if (bAddPlayerFlag)
        {
            bAddPlayerFlag = false;
            m_PlayerManager.Remove(dwPlayerID);
        }
    }
    return bResult;
}

void PlayerManager::RemovePlayer(int nConnIndex)
{
    bool bRetCode = false;
    Player* pPlayer = NULL;

    pPlayer = GetPlayer(nConnIndex);
    JYLOG_PROCESS_ERROR(pPlayer);

    bRetCode = m_NameManager.Remove(STString(pPlayer->m_szName));
    JYLOG_PROCESS_ERROR(bRetCode);

    printf("[PlayerManager] Player %s Logout.\n", pPlayer->m_szName);

    bRetCode = m_PlayerManager.Remove(pPlayer->m_dwPlayerID);
    JYLOG_PROCESS_ERROR(bRetCode);

    bRetCode = m_ConnIndexManager.Remove(nConnIndex);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_VOID_END
}

// Modify
bool PlayerManager::SetPlayerState(int nConnIndex, GameState eState)
{
    bool bResult = false;
    Player* pPlayer = NULL;
    PLAYER_STATE_TRIGGER* pTrigger = NULL;

    JYLOG_PROCESS_ERROR(eState >= egame_state_begin && eState < egame_state_end);

    pPlayer = GetPlayer(nConnIndex);
    JY_PROCESS_ERROR(pPlayer);
    JYLOG_PROCESS_ERROR(pPlayer->m_eState >= egame_state_begin && pPlayer->m_eState < egame_state_end);

    pTrigger = m_PlayerState[pPlayer->m_eState];
    JYLOG_PROCESS_ERROR(pTrigger);

    pTrigger->Leave(eState, pPlayer);

    pTrigger = m_PlayerState[eState];
    JYLOG_PROCESS_ERROR(pTrigger);

    pTrigger->Enter(pPlayer->m_eState, pPlayer);
    pPlayer->m_eState = eState;

    JY_STD_BOOL_END
}

// Query
bool PlayerManager::IsOnline(const char szName[])
{
    return m_NameManager.Find(STString(szName)) != NULL;
}

Player* PlayerManager::GetPlayer(DWORD dwPlayerID)
{
    return m_PlayerManager.Find(dwPlayerID);
}

Player* PlayerManager::GetPlayer(int nConnIndex)
{
    Player* pResult = NULL;
    DWORD* pdwPlayerID = NULL;

    pdwPlayerID = m_ConnIndexManager.Find(nConnIndex);
    JY_PROCESS_ERROR(pdwPlayerID);

    pResult = GetPlayer(*pdwPlayerID);
Exit0:
    return pResult;
}

Player* PlayerManager::GetPlayer(const char szName[])
{
    Player* pResult = NULL;
    DWORD* pdwPlayerID = NULL;

    pdwPlayerID = m_NameManager.Find(STString(szName));
    JY_PROCESS_ERROR(pdwPlayerID);

    pResult = GetPlayer(*pdwPlayerID);
Exit0:
    return pResult;
}