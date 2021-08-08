#include "stdafx.h"
#include "PlayerManager.h"

PlayerManager::PlayerManager()
{

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

bool PlayerManager::AddPlayer(int nConnIndex, const char szName[])
{
    bool bResult = false;
    bool bRetCode = false;
    DWORD dwPlayerID = ERROR_ID;
    Player* pPlayer = NULL;
    bool bAddNameFlag = false;
    bool bAddConnIndexFlag = false;
    bool bAddPlayerFlag = false;

    dwPlayerID = LoadPlayerFromDB(szName);
    JYLOG_PROCESS_ERROR(dwPlayerID);

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
    DWORD* pdwPlayerID = NULL;
    Player* pPlayer = NULL;

    pdwPlayerID = m_ConnIndexManager.Find(nConnIndex);
    JY_PROCESS_ERROR(pdwPlayerID);

    pPlayer = m_PlayerManager.Find(*pdwPlayerID);
    JYLOG_PROCESS_ERROR(pPlayer);

    bRetCode = m_NameManager.Remove(STString(pPlayer->m_szName));
    JYLOG_PROCESS_ERROR(bRetCode);

    printf("[PlayerManager] Player %s Logout.\n", pPlayer->m_szName);

    bRetCode = m_PlayerManager.Remove(*pdwPlayerID);
    JYLOG_PROCESS_ERROR(bRetCode);

    bRetCode = m_ConnIndexManager.Remove(nConnIndex);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_VOID_END
}

bool PlayerManager::IsOnline(const char szName[])
{
    return m_NameManager.Find(STString(szName)) != NULL;
}

DWORD PlayerManager::LoadPlayerFromDB(const char szName[])
{
    return szName[0];
}