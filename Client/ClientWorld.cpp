#include "stdafx.h"
#include "ClientWorld.h"

ClientWorld::ClientWorld()
{
    m_nPort = 0;
    m_bQuitFlag = false;
    memset(m_szIP, 0, sizeof(m_szIP));
}

ClientWorld::~ClientWorld()
{

}

bool ClientWorld::Init()
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

void ClientWorld::UnInit()
{
    m_Connection.UnInit();

}

void ClientWorld::Run()
{
    while (true)
    {
        JY_PROCESS_BREAK(!CheckQuitComplete());

        m_Connection.Active();

        Sleep(10);
    }
}


void ClientWorld::Quit()
{
    m_bQuitFlag = true;
    m_Connection.DisConnect();
}


bool ClientWorld::CheckQuitComplete()
{
    bool bResult = false;

    JY_PROCESS_ERROR(m_bQuitFlag);
    JY_PROCESS_ERROR(!m_Connection.IsEnable());

    JY_STD_BOOL_END;
}

bool ClientWorld::LoadConfig()
{
    bool bResult = false;

    strcpy(m_szIP, "127.0.0.1");
    m_nPort = 5566;

    JY_STD_BOOL_END
}