#include "stdafx.h"
#include "DBManager.h"

DBManager::DBManager()
{
    m_bRunFlag = false;
    m_pDBHandle = NULL;
    m_szSQL[0]  = '\0';
}

DBManager::~DBManager()
{
    assert(!m_pDBHandle);
}

bool DBManager::Init(const char cszDBAddr[], int nPort, const char cszUserName[], const char cszPassword[], const char cszDBName[])
{
    bool bResult = false;
    bool bRetCode = false;

    m_pDBHandle = MySQL_Connect(
        cszDBAddr, cszDBName, cszUserName, cszPassword, nPort
    );
    JY_PROCESS_ERROR(m_pDBHandle);

    bRetCode = CheckTable();
    JYLOG_PROCESS_ERROR(bRetCode);

    m_bRunFlag = true;

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (m_pDBHandle)
        {
            MySQL_Disconnect(m_pDBHandle);
            m_pDBHandle = NULL;
        }
    }
    return bResult;
}

void DBManager::UnInit()
{
    if (m_pDBHandle)
    {
        m_bRunFlag = false;
        MySQL_Disconnect(m_pDBHandle);
        m_pDBHandle = NULL;
    }
}

void DBManager::Quit()
{
    m_bRunFlag = false;
    if (m_pDBHandle)
    {
        MySQL_Disconnect(m_pDBHandle);
        m_pDBHandle = NULL;
    }
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

//////////////////////////////////////////////////////////////////////////
bool DBManager::CheckTable()
{
    bool bResult = false;
    bool bRetCode = false;
    int  nStrLen = 0;

    JYLOG_PROCESS_ERROR(m_pDBHandle);

    nStrLen = snprintf(m_szSQL, sizeof(m_szSQL),
        "create table if not exists %s "
        "("
        "   NickName    varchar(256)    not null,"
        "   Score       integer(20)     not null,"
        "   primary key (NickName)"
        ");", CUSTOM_PLAYER_INFO_TABLE_NAME
    );
    JY_PROCESS_ERROR(nStrLen > 0 && nStrLen < (int)sizeof(m_szSQL));

    bRetCode = DoQuery(m_szSQL);
    if (!bRetCode)
    {
        printf(
            "[DBManager] DB ERROR when try to create table \'%s\'",
            CUSTOM_PLAYER_INFO_TABLE_NAME
        );
        goto Exit0;
    }

    bResult = true;
Exit0:
    return bResult;
}

BOOL DBManager::DoQuery(const char cszSQL[], bool bSilentMode /*= false*/)
{
    BOOL     bRetCode = false;
    unsigned ulMySQLErrorCode = 0;

    assert(cszSQL);
    assert(m_pDBHandle);

    bRetCode = MySQL_Query(m_pDBHandle, cszSQL, &ulMySQLErrorCode, bSilentMode);

    if (!bRetCode && !bSilentMode)
    {
        printf("[DBManager] MySQL_Query failed in DoQuery : %u", ulMySQLErrorCode);

        if (ulMySQLErrorCode != 0 && ulMySQLErrorCode != ER_DUP_ENTRY) // 主键冲突不用断开链接
        {
            MySQL_Disconnect(m_pDBHandle);
            m_pDBHandle = NULL;
        }
    }

    return bRetCode;
}