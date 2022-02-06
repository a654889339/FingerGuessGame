#include "stdafx.h"
#include "GameCenter.h"

GameCenter::GameCenter()
{

}

GameCenter::~GameCenter()
{

}

bool GameCenter::Init()
{
    bool bResult              = false;
    bool bRetCode             = false;
    bool bInitRouterAgentFlag = false;

    bRetCode = m_RouterAgent.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bInitRouterAgentFlag = true;

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bInitRouterAgentFlag)
        {
            m_RouterAgent.UnInit();
            bInitRouterAgentFlag = false;
        }
    }
    return bResult;
}

void GameCenter::UnInit()
{
    m_RouterAgent.UnInit();
}

void GameCenter::Run()
{
    while (true)
    {
        m_RouterAgent.Active();
        Sleep(10);
    }
}

void GameCenter::Quit()
{

}