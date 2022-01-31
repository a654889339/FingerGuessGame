#include "stdafx.h"
#include "RouterModule.h"

RouterModule::RouterModule()
{
    m_eModuleType = ermt_begin;
    m_nConnIndex  = -1;
}

RouterModule::~RouterModule()
{

};

bool RouterModule::Init(RouterModuleType eType, int nConnIndex, const char szIP[], int nPort)
{
    bool bResult  = false;
    bool bRetCode = false;
    int  nRetCode = 0;

    JYLOG_PROCESS_ERROR(szIP);

    m_eModuleType = eType;
    m_nConnIndex  = nConnIndex;
    m_nPort       = nPort;

    strncpy(m_szIP, szIP, sizeof(m_szIP));

    m_Thread.Create(&WorkThread, this);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void RouterModule::UnInit()
{
    m_Thread.Destroy();
    Quit();
}


void RouterModule::WorkThread(void* pvParam)
{
    RouterModule* pThis = (RouterModule*)pvParam;

    assert(pvParam);

    pThis->Run();
}

void RouterModule::Run()
{
    while (true)
    {
        if (IsEnable())
        {
            ProcessNetwork();
        }
        else
        {
            Bind(m_szIP, m_nPort);
        }

        Sleep(1);
    }
}

void RouterModule::ProcessPackage(int nConnIndex, BYTE* pbyData, size_t uDataLen)
{

}

void RouterModule::NewConnection(int nConnIndex, int* pnIP, int nPort)
{

}

void RouterModule::DisConnection(int nConnIndex)
{

}
