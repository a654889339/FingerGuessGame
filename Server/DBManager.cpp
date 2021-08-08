#include "stdafx.h"
#include "DBManager.h"

DBManager::DBManager()
{
    m_bRunFlag = false;
}

DBManager::~DBManager()
{

}

bool DBManager::Init()
{
    m_bRunFlag = true;
    return true;
}

void DBManager::UnInit()
{

}

void DBManager::Quit()
{
    m_bRunFlag = false;
}

bool DBManager::IsEnable()
{
    return m_bRunFlag;
}

DWORD DBManager::LoadPlayerIDByName(const char szName[])
{
    return szName[0];
}

bool DBManager::LoadPlayer(Player* pPlayer)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(pPlayer);
    JYLOG_PROCESS_ERROR(pPlayer->m_dwPlayerID != ERROR_ID);

    JY_STD_BOOL_END
}