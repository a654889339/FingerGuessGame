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
    BOOL bAddFlag = false;

    dwPlayerID = GetPlayerID(szName);
    JYLOG_PROCESS_ERROR(dwPlayerID);

    pPlayer = m_PlayerManager.Add(dwPlayerID);
    JYLOG_PROCESS_ERROR(pPlayer);
    bAddFlag = true;

    bRetCode = pPlayer->Init(dwPlayerID, nConnIndex, szName);
    JYLOG_PROCESS_ERROR(bRetCode);


    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bAddFlag)
        {
            bAddFlag = false;
            m_PlayerManager.Remove(dwPlayerID);
        }
    }
    return bResult;
}

DWORD PlayerManager::GetPlayerID(const char szName[])
{
    return szName[0];
}