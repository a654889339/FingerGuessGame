#include "stdafx.h"
#include "ClientLogic.h"
#include <mutex>

// -------------------------------------------- DLL Export Begin --------------------------------------------
CLIENT_LOGIC_DLL_API IClientLogic* CreateClientLogic()
{
    IClientLogic* pResult = NULL;
    bool          bRetCode = false;

    pResult = (IClientLogic*)new ClientLogic();
    JYLOG_PROCESS_ERROR(pResult);

    bRetCode = pResult->Init();
    if (!bRetCode)
    {
        delete pResult;
        pResult = NULL;
        JYLOG_PROCESS_ERROR(false);
    }

Exit0:
    return pResult;
}

CLIENT_LOGIC_DLL_API void DestroyClientLogic(IClientLogic* pClientLogic)
{
    JYLOG_PROCESS_ERROR(pClientLogic);

    pClientLogic->UnInit();

    delete pClientLogic;
    pClientLogic = NULL;

    JY_STD_VOID_END
}

CLIENT_LOGIC_DLL_API bool Send(BYTE* pbyData, size_t uDataLen)
{
    bool bResult = false;

    bool bRetCode = g_pClient->PushE2C(pbyData, uDataLen);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

CLIENT_LOGIC_DLL_API bool Recv(size_t uLimitSize, BYTE* pbyData, size_t* puDataLen)
{
    bool bResult = false;

    bool bRetCode = g_pClient->PopC2E(uLimitSize, pbyData, puDataLen);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

// -------------------------------------------- DLL Export End --------------------------------------------

ClientLogic::ClientLogic()
{
    m_bQuitFlag = false;
    m_nTimeNow = 0;
    m_nGatePort = 0;

    memset(m_szGateIP, 0, sizeof(m_szGateIP));
}

ClientLogic::~ClientLogic()
{

}

bool ClientLogic::Init()
{
    bool bResult           = false;
    bool bRetCode          = false;
    bool bControlInitFlag  = false;
    bool bStateMgrInitFlag = false;

    m_nTimeNow = time(NULL);

    bRetCode = LoadConfig();
    JYLOG_PROCESS_ERROR(bRetCode);

    bRetCode = m_Control.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bControlInitFlag = true;

    bRetCode = m_ClientStateManager.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bStateMgrInitFlag = true;

    bResult = true;
Exit0:
    if (!bResult)
    {
        if (bStateMgrInitFlag)
        {
            m_ClientStateManager.UnInit();
            bStateMgrInitFlag = false;
        }

        if (bControlInitFlag)
        {
            m_Control.UnInit();
            bControlInitFlag = false;
        }
    }
    return bResult;
}

void ClientLogic::UnInit()
{
    m_ClientStateManager.UnInit();
    m_Control.UnInit();
}

void ClientLogic::Run()
{
    while (true)
    {
        m_nTimeNow = time(NULL);

        JY_PROCESS_ERROR(!CheckQuitComplete());

        ProcessEngineMsg();
        m_ClientStateManager.Active();
    }

    JY_STD_VOID_END
}

void ClientLogic::Quit()
{
    m_bQuitFlag = true;
    m_ClientStateManager.UnInit();
}


bool ClientLogic::PushE2C(BYTE* pbyData, size_t uDataLen)
{
    bool bResult  = false;
    bool bRetCode = false;

    JYLOG_PROCESS_ERROR(pbyData);

    bRetCode = m_E2CQueue.Push(pbyData, uDataLen);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

bool ClientLogic::PopC2E(size_t uLimitSize, BYTE* pbyData, size_t* puDataLen)
{
    bool bResult  = false;
    bool bRetCode = false;

    JYLOG_PROCESS_ERROR(pbyData);

    bRetCode = m_C2EQueue.Pop(uLimitSize, pbyData, puDataLen);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

// Private
bool ClientLogic::PushC2E(BYTE* pbyData, size_t uDataLen)
{
    bool bResult  = false;
    bool bRetCode = false;

    JYLOG_PROCESS_ERROR(pbyData);

    bRetCode = m_C2EQueue.Push(pbyData, uDataLen);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END

}

bool ClientLogic::PopE2C(size_t uLimitSize, BYTE* pbyData, size_t* puDataLen)
{
    bool bResult  = false;
    bool bRetCode = false;

    JYLOG_PROCESS_ERROR(pbyData);

    bRetCode = m_E2CQueue.Pop(uLimitSize, pbyData, puDataLen);
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ClientLogic::ProcessEngineMsg()
{

}

bool ClientLogic::CheckQuitComplete()
{
    bool bResult = false;

    JY_PROCESS_ERROR(m_bQuitFlag);
    JY_PROCESS_ERROR(!m_Connection.IsEnable());

    JY_STD_BOOL_END;
}

bool ClientLogic::LoadConfig()
{
    bool bResult = false;


    JY_STD_BOOL_END
}
