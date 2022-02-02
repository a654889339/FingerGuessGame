#include "stdafx.h"
#include "RouterModuleAgent.h"

RouterModuleAgent::RouterModuleAgent()
{
    m_eType = ermt_begin;
}

RouterModuleAgent::~RouterModuleAgent()
{

}

bool RouterModuleAgent::Init(RouterModuleType eType)
{
    bool bResult  = false;
    bool bRetCode = false;

    JYLOG_PROCESS_ERROR(eType > ermt_begin && eType < ermt_end);

    m_eType = eType;

    m_Thread.Create(&WorkThread, this);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void RouterModuleAgent::UnInit()
{
    Quit();
}

bool RouterModuleAgent::Recv(size_t uLimitSize, BYTE* pbyData, size_t* puDataLen)
{
    bool bResult = false;



    JY_STD_BOOL_END
}

bool RouterModuleAgent::SendToModule(BYTE* pbyData, size_t uDataLen)
{
    return m_SendQueue.Push(pbyData, uDataLen);
}

//// Private
void RouterModuleAgent::WorkThread(void* pvParam)
{
    RouterModuleAgent* pThis = (RouterModuleAgent*)pvParam;

    JYLOG_PROCESS_ERROR(pThis);

    pThis->Run();

    JY_STD_VOID_END
}


void RouterModuleAgent::Run()
{
    while (true)
    {
        if (IsEnable())
        {
            SendFlush();
            ProcessNetwork();
        }
        else
        {
            Connect(szRouterModuleIPConfig[m_eType], szRouterModulePortConfig[m_eType]);
        }

        Sleep(1);
    }
}

void RouterModuleAgent::ProcessPackage(BYTE* pbyData, size_t uDataLen)
{
    bool                  bRetCode = false;
    RouterProtocolHeader* pHeader  = (RouterProtocolHeader*)pbyData;

    JYLOG_PROCESS_ERROR(pHeader);
    JYLOG_PROCESS_ERROR(uDataLen >= sizeof(RouterProtocolHeader));

    bRetCode = m_RecvQueue.Push(pbyData, uDataLen);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_VOID_END
}

void RouterModuleAgent::ConnectionLost()
{

}

void RouterModuleAgent::SendFlush()
{
    bool   bRetCode = false;
    BYTE*  pbyData  = m_byTempBuffer;
    size_t uDataLen = 0;

    while (true)
    {
        bRetCode = m_SendQueue.TryPop(sizeof(m_byTempBuffer), pbyData, &uDataLen);
        JY_PROCESS_ERROR(bRetCode);

        bRetCode = Send(pbyData, uDataLen);
        JYLOG_PROCESS_ERROR(bRetCode);
    }

    JY_STD_VOID_END
}