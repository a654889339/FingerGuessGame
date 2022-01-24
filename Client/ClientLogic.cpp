#include "stdafx.h"
#include <mutex>
#include "ClientLogic.h"

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
    memset(m_ProcessProtocolFuns, 0, sizeof(m_ProcessProtocolFuns));
    memset(m_nProtocolSize, 0, sizeof(m_nProtocolSize));

    REGISTER_EXTERNAL_FUNC(ege2c_login_request, &ClientLogic::OnLoginRequest, sizeof(GE2C_LOGIN_REQUEST));
}

ClientLogic::~ClientLogic()
{

}

bool ClientLogic::Init()
{
    bool        bResult           = false;
    bool        bRetCode          = false;
    bool        bControlInitFlag  = false;
    bool        bStateMgrInitFlag = false;
    bool        bThreadCreate     = false;

    m_nTimeNow = time(NULL);

    bRetCode = LoadConfig();
    JYLOG_PROCESS_ERROR(bRetCode);

    bRetCode = m_Control.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bControlInitFlag = true;

    bRetCode = m_ClientStateManager.Init();
    JYLOG_PROCESS_ERROR(bRetCode);
    bStateMgrInitFlag = true;

#ifdef CLIENT_LOGIC_DLL_API
    m_DLLThread.Create(&WorkThread, this);
    JYLOG_PROCESS_ERROR(bRetCode);
    bThreadCreate = true;
#endif

    bResult = true;
Exit0:
    if (!bResult)
    {
#ifdef CLIENT_LOGIC_DLL_API
        if (bThreadCreate)
        {
            m_DLLThread.Destroy();
            bThreadCreate = false;
        }
#endif

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
#ifdef CLIENT_LOGIC_DLL_API
    m_DLLThread.Destroy();
#endif
    m_ClientStateManager.UnInit();
    m_Control.UnInit();
}

void ClientLogic::WorkThread(void* pvParam)
{
    ClientLogic* pThis = (ClientLogic*)pvParam;

    assert(pThis);

    pThis->Run();
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
    JY_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

// Private
void ClientLogic::OnLoginRequest(BYTE* pbyData, size_t uSize)
{
    GE2C_LOGIN_REQUEST* pRequest = (GE2C_LOGIN_REQUEST*)pbyData;

    JYLOG_PROCESS_ERROR(pRequest);

    printf("[ClientLogic] OnLoginRequest: %d.", pRequest->nTestNum);

    JY_STD_VOID_END
}


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
    JY_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}

void ClientLogic::ProcessEngineMsg()
{
    bool   bRetCode = false;
    BYTE*  pbyData  = NULL;
    size_t uDataLen = 0;

    while (true)
    {
        pbyData = m_byEngineMsgBuffer;
        JYLOG_PROCESS_ERROR(pbyData);

        bRetCode = PopE2C(sizeof(m_byEngineMsgBuffer), pbyData, &uDataLen);
        JY_PROCESS_ERROR(bRetCode);

        ProcessPackage(pbyData, uDataLen);
    }

    JY_STD_VOID_END
}

void ClientLogic::ProcessPackage(BYTE* pbyData, size_t uDataLen)
{
    CLIENT_GAME_ENGINE_PROTOCOL_HEADER* pHeader = (CLIENT_GAME_ENGINE_PROTOCOL_HEADER*)pbyData;
    PROCESS_PROTOCOL_FUNC               Func    = NULL;

    JYLOG_PROCESS_ERROR(pbyData);
    JYLOG_PROCESS_ERROR(uDataLen >= sizeof(CLIENT_GAME_ENGINE_PROTOCOL_HEADER));
    JYLOG_PROCESS_ERROR(ege2c_begin < pHeader->wProtocolID && pHeader->wProtocolID < ege2c_end);

    if (m_nProtocolSize[pHeader->wProtocolID] != UNDEFINED_PROTOCOL_SIZE)
    {
        JYLOG_PROCESS_ERROR(uDataLen == m_nProtocolSize[pHeader->wProtocolID]);
    }

    Func = m_ProcessProtocolFuns[pHeader->wProtocolID];
    JYLOG_PROCESS_ERROR(Func);

    (this->*Func)(pbyData, uDataLen);

    JY_STD_VOID_END;
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
