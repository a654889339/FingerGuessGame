#include "stdafx.h"
#include "RouterModule.h"

RouterModule::RouterModule()
{
    m_eModuleType = ermt_begin;
    m_nIndex      = -1;
    m_nConnIndex  = -1;
    m_nPort       = 0;
    m_szIP[0]     = '\0';
}

RouterModule::~RouterModule()
{

};

bool RouterModule::Init(RouterModuleType eType, int nIndex, const char szIP[], int nPort)
{
    bool bResult  = false;
    bool bRetCode = false;
    int  nRetCode = 0;

    JYLOG_PROCESS_ERROR(szIP);

    m_eModuleType = eType;
    m_nIndex      = nIndex;
    m_nPort       = nPort;

    strncpy(m_szIP, szIP, sizeof(m_szIP));
    m_szIP[sizeof(m_szIP) - 1] = '\0';

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
            SendFlush();
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
    bool                  bRetCode = false;
    RouterProtocolHeader* pHeader  = (RouterProtocolHeader*)pbyData;

    JYLOG_PROCESS_ERROR(pHeader);
    JYLOG_PROCESS_ERROR(uDataLen >= sizeof(RouterProtocolHeader));
    JYLOG_PROCESS_ERROR(uDataLen == sizeof(RouterProtocolHeader) + pHeader->uDataLen);

    bRetCode = m_C2SQueue.Push(pbyData, uDataLen);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_VOID_END
}

void RouterModule::NewConnection(int nConnIndex, int* pnIP, int nPort)
{
    m_nConnIndex = nConnIndex;
}

void RouterModule::DisConnection(int nConnIndex)
{
    m_nConnIndex = -1;
}

void RouterModule::SendFlush()
{
    bool   bRetCode = false;
    size_t uDataLen = 0;

    while (true)
    {
        bRetCode = m_S2CQueue.Pop(sizeof(m_byTempSize), m_byTempSize, &uDataLen);
        JY_PROCESS_ERROR(bRetCode);

        bRetCode = Send(m_nConnIndex, m_byTempSize, uDataLen);
        JYLOG_PROCESS_ERROR(bRetCode);
    }

    JY_STD_VOID_END
}