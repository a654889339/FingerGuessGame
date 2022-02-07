#include "stdafx.h"
#include "RouterModule.h"

RouterModule::RouterModule()
{
    m_eModuleType = ermt_begin;
    m_nConnIndex  = -1;
    m_nPort       = 0;
    m_szIP[0]     = '\0';
}

RouterModule::~RouterModule()
{

};

bool RouterModule::Init(RouterModuleType eType, const char szIP[], int nPort)
{
    bool bResult  = false;
    bool bRetCode = false;
    int  nRetCode = 0;

    JYLOG_PROCESS_ERROR(szIP);

    m_eModuleType = eType;
    m_nPort       = nPort;

    strncpy(m_szIP, szIP, sizeof(m_szIP));
    m_szIP[sizeof(m_szIP) - 1] = '\0';

    bRetCode = m_Thread.Create(&WorkThread, this);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void RouterModule::UnInit()
{
    m_Thread.Destroy();
    Quit();
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
            printf("[RouterModule] Bind %s:%d succeed.\n", m_szIP, m_nPort);
        }

        Sleep(1);
    }
}

IJYBuffer* RouterModule::Recv()
{
    // it may always fail if module send message frequently.
    return m_RecvQueue.TryPop();
}

bool RouterModule::SendToModule(IJYBuffer* piBuffer)
{
    bool bResult = false;

    JYLOG_PROCESS_ERROR(m_SendQueue.Push(piBuffer));

    JY_STD_BOOL_END
}

//// Private
void RouterModule::WorkThread(void* pvParam)
{
    RouterModule* pThis = (RouterModule*)pvParam;

    assert(pvParam);

    pThis->Run();
}

void RouterModule::ProcessPackage(int nConnIndex, BYTE* pbyData, size_t uDataLen)
{
    bool                  bRetCode = false;
    RouterProtocolHeader* pHeader  = (RouterProtocolHeader*)pbyData;

    JYLOG_PROCESS_ERROR(pHeader);
    JYLOG_PROCESS_ERROR(uDataLen >= sizeof(RouterProtocolHeader));
    JYLOG_PROCESS_ERROR(uDataLen == pHeader->uDataLen);

    bRetCode = m_RecvQueue.Push(pbyData, uDataLen);
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
        bRetCode = m_SendQueue.Pop(sizeof(m_byTempSize), m_byTempSize, &uDataLen);
        JY_PROCESS_ERROR(bRetCode);

        bRetCode = Send(m_nConnIndex, m_byTempSize, uDataLen);
        JYLOG_PROCESS_ERROR(bRetCode);
    }

    JY_STD_VOID_END
}