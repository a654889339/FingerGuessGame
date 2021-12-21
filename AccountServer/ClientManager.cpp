#include "stdafx.h"
#include "ClientManager.h"


ClientManager::ClientManager()
{

}

ClientManager::~ClientManager()
{

}

bool ClientManager::Init()
{
    bool bResult = false;

    JY_STD_BOOL_END
}

void ClientManager::UnInit()
{

}


bool ClientManager::Add(const char szAccountName[], int nConnIndex)
{
    bool            bResult  = false;
    bool            bRetCode = false;
    ClientLoginInfo Info;

    JYLOG_PROCESS_ERROR(szAccountName);

    strcpy(Info.szAccountName, szAccountName);

    JY_PROCESS_ERROR(m_InfoManager.find(Info) == NULL);

    bRetCode = m_InfoManager.add(Info, nConnIndex);
    JYLOG_PROCESS_ERROR(bRetCode);

    bRetCode = m_ConnManager.add(nConnIndex, Info);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ClientManager::Del(int nConnIndex)
{

}