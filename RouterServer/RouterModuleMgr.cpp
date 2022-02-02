#include "stdafx.h"
#include "RouterModuleMgr.h"

RouterModuleMgr::RouterModuleMgr()
{
    memset(m_byTempBuffer, 0, sizeof(m_byTempBuffer));
}

RouterModuleMgr::~RouterModuleMgr()
{

}

bool RouterModuleMgr::Init()
{
    bool bResult  = false;
    bool bRetCode = false;

    for (int i = ermt_begin + 1; i < ermt_end; i++)
    {
        bRetCode = m_szModule[i].Init((RouterModuleType)i, szRouterModuleIPConfig[i], szRouterModulePortConfig[i]);
        JYLOG_PROCESS_ERROR(bRetCode);
    }

    JY_STD_BOOL_END
}

void RouterModuleMgr::UnInit()
{
    for (int i = ermt_begin + 1; i < ermt_end; i++)
    {
        m_szModule[i].UnInit();
    }
}

void RouterModuleMgr::Run()
{
    for (int i = ermt_begin + 1; i < ermt_end; i++)
    {
        ProcessModule(&m_szModule[i]);
    }
}

//// Private
void RouterModuleMgr::ProcessModule(RouterModule* pModule)
{
    bool                  bRetCode   = false;
    BYTE*                 pbyData    = m_byTempBuffer;
    size_t                uDataLen   = 0;
    RouterProtocolHeader* pHeader    = NULL;
    RouterModule*         pDstModule = NULL;

    JYLOG_PROCESS_ERROR(pModule);

    while (true)
    {
        bRetCode = pModule->Recv(sizeof(m_byTempBuffer), pbyData, &uDataLen);
        JY_PROCESS_ERROR(bRetCode);

        JYLOG_PROCESS_ERROR(uDataLen >= sizeof(RouterProtocolHeader));

        pHeader = (RouterProtocolHeader*)pbyData;
        JYLOG_PROCESS_ERROR(pHeader);

        pDstModule = GetModule((RouterModuleType)pHeader->nModuleType);
        JYLOG_PROCESS_ERROR(pDstModule);

        pHeader->nModuleType = pModule->GetType();

        bRetCode = pDstModule->SendToModule(pbyData, uDataLen);
        JYLOG_PROCESS_ERROR(bRetCode);
    }

    JY_STD_VOID_END
}

RouterModule* RouterModuleMgr::GetModule(RouterModuleType eType)
{
    RouterModule* pResult = NULL;

    JYLOG_PROCESS_ERROR(eType > ermt_begin && eType < ermt_end);

    pResult = &m_szModule[eType];
Exit0:
    return pResult;
}