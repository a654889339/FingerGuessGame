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
    m_PlayerMap.clear();
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

    bRetCode = m_NameManager.add(STString(szName), dwPlayerID);
    JYLOG_PROCESS_ERROR(bRetCode);
    bAddNameFlag = true;

    bRetCode = m_ConnIndexManager.add(nConnIndex, dwPlayerID);
    JYLOG_PROCESS_ERROR(bRetCode);
    bAddConnIndexFlag = true;

    pPlayer = m_PlayerMap.add(dwPlayerID);
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
            m_NameManager.remove(szName);
        }

        if (bAddConnIndexFlag)
        {
            bAddConnIndexFlag = false;
            m_ConnIndexManager.remove(nConnIndex);
        }

        if (bAddPlayerFlag)
        {
            bAddPlayerFlag = false;
            m_PlayerMap.remove(dwPlayerID);
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

    bRetCode = m_NameManager.remove(STString(pPlayer->m_szName));
    JYLOG_PROCESS_ERROR(bRetCode);

    printf("[PlayerManager] Player %s Logout.\n", pPlayer->m_szName);

    bRetCode = m_PlayerMap.remove(pPlayer->m_dwPlayerID);
    JYLOG_PROCESS_ERROR(bRetCode);

    bRetCode = m_ConnIndexManager.remove(nConnIndex);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_VOID_END
}

// Modify
bool PlayerManager::SetState(int nConnIndex, GameState eState)
{
    bool bResult = false;
    bool bRetCode = false;
    Player* pPlayer = NULL;

    pPlayer = GetPlayer(nConnIndex);
    JYLOG_PROCESS_ERROR(pPlayer);

    bRetCode = SetPlayerState(pPlayer, eState);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}
// Query
bool PlayerManager::IsOnline(const char szName[])
{
    return m_NameManager.find(STString(szName)) != NULL;
}

Player* PlayerManager::GetPlayer(DWORD dwPlayerID)
{
    return m_PlayerMap.find(dwPlayerID);
}

Player* PlayerManager::GetPlayer(int nConnIndex)
{
    Player* pResult = NULL;
    DWORD* pdwPlayerID = NULL;

    pdwPlayerID = m_ConnIndexManager.find(nConnIndex);
    JY_PROCESS_ERROR(pdwPlayerID);

    pResult = GetPlayer(*pdwPlayerID);
Exit0:
    return pResult;
}

Player* PlayerManager::GetPlayer(const char szName[])
{
    Player* pResult = NULL;
    DWORD* pdwPlayerID = NULL;

    pdwPlayerID = m_NameManager.find(STString(szName));
    JY_PROCESS_ERROR(pdwPlayerID);

    pResult = GetPlayer(*pdwPlayerID);
Exit0:
    return pResult;
}
