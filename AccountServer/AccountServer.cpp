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
    bool bRouterAgentInitFlag   = false;

    bRetCode = m_ClientAgent.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bClientAgentInitFlag = true;

    bRetCode = m_ClientManager.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bClientManagerInitFlag = true;

    bRetCode = m_RouterAgent.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bRouterAgentInitFlag = true;

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bRouterAgentInitFlag)
        {
            m_RouterAgent.UnInit();
            bRouterAgentInitFlag = false;
        }

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
    m_RouterAgent.UnInit();
    m_ClientManager.UnInit();
    m_ClientAgent.UnInit();
}

void AccountServer::Run()
{
    while (true)
    {
        m_ClientAgent.Active();
        m_RouterAgent.Active();

        Sleep(10);
    }
}

void AccountServer::Quit()
{
    m_ClientAgent.Quit();
}