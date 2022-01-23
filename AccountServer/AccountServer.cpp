#include "stdafx.h"
#include "AccountServer.h"

AccountServer::AccountServer()
{

}

AccountServer::~AccountServer()
{

}

bool AccountServer::Init()
{
    bool bResult                = false;
    bool bRetCode               = false;
    bool bClientAgentInitFlag   = false;
    bool bClientManagerInitFlag = false;

    bRetCode = m_ClientAgent.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bClientAgentInitFlag = true;

    bRetCode = m_ClientManager.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bClientManagerInitFlag = true;

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bClientManagerInitFlag)
        {
            m_ClientManager.UnInit();
            bClientManagerInitFlag = false;
        }

        if (bClientAgentInitFlag)
        {
            m_ClientAgent.UnInit();
            bClientAgentInitFlag = false;
        }
    }
    return bResult;
}

void AccountServer::UnInit()
{
    m_ClientManager.UnInit();
    m_ClientAgent.UnInit();
}

void AccountServer::Run()
{
    while (true)
    {
        m_ClientAgent.Active();

        Sleep(10);
    }
}

void AccountServer::Quit()
{
    m_ClientAgent.Quit();
}