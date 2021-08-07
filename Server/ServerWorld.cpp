#include "stdafx.h"
#include "ServerWorld.h"

ServerWorld::ServerWorld()
{
    m_nPort = 0;
    m_bQuitFlag = false;

    memset(m_szIP, 0, sizeof(m_szIP));
}

ServerWorld::~ServerWorld()
{

}

bool ServerWorld::Init()
{
    bool bResult = false;
    bool bRetCode = false;
    bool bConnInitFlag = false;

    bRetCode = LoadConfig();
    JYLOG_PROCESS_ERROR(bRetCode);

    bRetCode = m_Connection.Init(m_szIP, m_nPort);
    JYLOG_PROCESS_ERROR(bRetCode);
    bConnInitFlag = true;

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bConnInitFlag)
        {
            bConnInitFlag = false;
            m_Connection.UnInit();
        }
    }
    return bResult;
}

void ServerWorld::UnInit()
{
    m_Connection.UnInit();
}

void ServerWorld::Run()
{
    while(true)
    {
        m_Connection.Active();
        Sleep(10);
    }
}

void ServerWorld::Quit()
{
    m_bQuitFlag = true;
}

//////////////////////////////////////////////////////////////////////////

bool ServerWorld::LoadConfig()
{
    bool bResult = false;

    strcpy(m_szIP, "127.0.0.1");
    m_nPort = 5566;

    JY_STD_BOOL_END
}