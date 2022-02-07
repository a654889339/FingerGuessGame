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

    bRetCode = m_Thread.Create(&WorkThread, this);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void RouterModuleAgent::UnInit()
{
    m_Thread.Destroy();
    Quit();
}

bool RouterModuleAgent::Recv(size_t uLimitSize, BYTE* &pbyData, size_t* puDataLen, RouterModuleType* peType, uint16_t* pnProtocolID)
{
    bool                  bResult  = false;
    bool                  bRetCode = false;
    RouterProtocolHeader* pHeader  = NULL;

    JYLOG_PROCESS_ERROR(puDataLen);
    JYLOG_PROCESS_ERROR(peType);
    JYLOG_PROCESS_ERROR(pnProtocolID);

    bRetCode = m_RecvQueue.Pop(uLimitSize, pbyData, puDataLen);
    JY_PROCESS_ERROR(bRetCode);

    pHeader = (RouterProtocolHeader*)pbyData;
    JYLOG_PROCESS_ERROR(pHeader);
    JYLOG_PROCESS_ERROR(*puDataLen >= sizeof(RouterProtocolHeader));
    JYLOG_PROCESS_ERROR(pHeader->nModuleType > ermt_begin && pHeader->nModuleType < ermt_end);

    *peType       = (RouterModuleType)pHeader->nModuleType;
    *pnProtocolID = pHeader->nProtocolID;
    pbyData       = pHeader->byData;
    *puDataLen    -= sizeof(RouterProtocolHeader);

    JY_STD_BOOL_END
}

bool RouterModuleAgent::SendToModule(RouterModuleType eType, uint16_t nProtocolID, BYTE* pbyData, size_t uDataLen)
{
    bool                  bResult  = false;
    bool                  bRetCode = false;
    IJYBuffer*            piBuffer = NULL;
    RouterProtocolHeader* pHeader  = NULL;

    JYLOG_PROCESS_ERROR(pbyData);
    JYLOG_PROCESS_ERROR(uDataLen);

    piBuffer = JYMemoryCreate(uDataLen + sizeof(RouterProtocolHeader));
    JYLOG_PROCESS_ERROR(piBuffer);

    pHeader = (RouterProtocolHeader*)piBuffer->GetData();
    JYLOG_PROCESS_ERROR(pHeader);

    pHeader->nModuleType = eType;
    pHeader->nProtocolID = nProtocolID;
    pHeader->uDataLen    = (uint32_t)piBuffer->GetSize();

    memcpy(pHeader->byData, pbyData, uDataLen);

    bRetCode = m_SendQueue.Push(piBuffer);
    JYLOG_PROCESS_ERROR(bRetCode);

    bResult = true;
Exit0:
    JYMemoryDelete(piBuffer);
    return bResult;
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
            printf("[RouterModuleAgent] Connect to %s:%d succeed.\n", szRouterModuleIPConfig[m_eType], szRouterModulePortConfig[m_eType]);
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
    BYTE*  pbyData  = m_byThreadBuffer;
    size_t uDataLen = 0;

    while (true)
    {
        bRetCode = m_SendQueue.TryPop(sizeof(m_byThreadBuffer), pbyData, &uDataLen);
        JY_PROCESS_ERROR(bRetCode);

        bRetCode = Send(pbyData, uDataLen);
        JYLOG_PROCESS_ERROR(bRetCode);
    }

    JY_STD_VOID_END
}