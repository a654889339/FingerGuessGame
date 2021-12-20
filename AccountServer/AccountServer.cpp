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
    bool bResult              = false;
    bool bRetCode             = false;
    bool bClientAgentInitFlag = false;

    bRetCode = m_ClientAgent.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bClientAgentInitFlag = true;

    bResult = true;
Exit0:
    if (!bResult)
    {
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
    m_ClientAgent.UnInit();
}

void AccountServer::Run()
{
    m_ClientAgent.Active();

    Sleep(10);
}

void AccountServer::Quit()
{
    m_ClientAgent.Quit();
}