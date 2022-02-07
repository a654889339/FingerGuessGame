#include "stdafx.h"
#include "RouterServer.h"

RouterServer::RouterServer()
{

}

RouterServer::~RouterServer()
{

}

bool RouterServer::Init()
{
    bool bResult            = false;
    bool bRetCode           = false;
    bool bInitModuleMgrFlag = false;

    bRetCode = m_ModuleMgr.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bInitModuleMgrFlag = true;

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bInitModuleMgrFlag)
        {
            m_ModuleMgr.UnInit();
            bInitModuleMgrFlag = false;
        }
    }
    return bResult;
}

void RouterServer::UnInit()
{
    m_ModuleMgr.UnInit();
}

void RouterServer::Run()
{
    while (true)
    {
        m_ModuleMgr.Active();

        Sleep(1);
    }
}

void RouterServer::Quit()
{

}
