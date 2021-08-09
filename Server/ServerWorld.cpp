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
    bool bPlayerManagerInitFlag = false;
    bool bDBInitFlag = false;
    bool bConnInitFlag = false;

    bRetCode = LoadConfig();
    JYLOG_PROCESS_ERROR(bRetCode);

    bRetCode = m_PlayerManager.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bPlayerManagerInitFlag = true;

    bRetCode = m_DB.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bDBInitFlag = true;

    bRetCode = m_Connection.Init(m_szIP, m_nPort);
    JYLOG_PROCESS_ERROR(bRetCode);
    bConnInitFlag = true;

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bPlayerManagerInitFlag)
        {
            bPlayerManagerInitFlag = false;
            m_PlayerManager.UnInit();
        }

        if (bConnInitFlag)
        {
            bConnInitFlag = false;
            m_Connection.UnInit();
        }

        if (bDBInitFlag)
        {
            bDBInitFlag = false;
            m_DB.UnInit();
        }
    }
    return bResult;
}

void ServerWorld::UnInit()
{
    m_PlayerManager.UnInit();
    m_Connection.UnInit();
    m_DB.UnInit();
}

void ServerWorld::Run()
{
    while(true)
    {
        JY_PROCESS_ERROR(!CheckQuitComplete());

        //m_DB.Active();
        m_Connection.Active();

        Sleep(10);
    }

    JY_STD_VOID_END
}

void ServerWorld::Quit()
{
    m_bQuitFlag = true;
    m_Connection.Quit();
    m_DB.Quit();
}

bool ServerWorld::CheckQuitComplete()
{
    bool bResult = false;

    JY_PROCESS_ERROR(m_bQuitFlag);
    JY_PROCESS_ERROR(!m_Connection.IsEnable());
    JY_PROCESS_ERROR(!m_DB.IsEnable());

    JY_STD_BOOL_END;
}

//////////////////////////////////////////////////////////////////////////

bool ServerWorld::LoadConfig()
{
    bool bResult = false;

    strcpy(m_szIP, "127.0.0.1");
    m_nPort = 5566;

    JY_STD_BOOL_END
}