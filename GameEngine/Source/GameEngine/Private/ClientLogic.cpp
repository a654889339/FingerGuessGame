#include "ClientLogic.h"

#include "../../Base/stdafx.h"

ClientLogic::ClientLogic()
{
}

ClientLogic::~ClientLogic()
{
}

bool ClientLogic::Init()
{
    bool    bResult                    = false;
    FString ClientLogicDllName         = TEXT("ClientX64D.dll");
    FString FuncNameCreateClientLogic  = TEXT("CreateClientLogic");
    FString FuncNameDestroyClientLogic = TEXT("DestroyClientLogic");
    FString DllPath                    = "../../ThirdParty/Win64/" + ClientLogicDllName;

    m_pClientLogicDLL_Handle = FPlatformProcess::GetDllHandle(*DllPath);
    JYLOG_PROCESS_ERROR(m_pClientLogicDLL_Handle);

    m_pFuncCreateClientLogic = (CREAT_CLIENT_LOGIC_FUNC)FPlatformProcess::GetDllExport(m_pClientLogicDLL_Handle, *FuncNameCreateClientLogic);
    JYLOG_PROCESS_ERROR(m_pFuncCreateClientLogic);

    m_pFuncDestroyClientLogic = (DESTROY_CLIENT_LOGIC_FUNC)FPlatformProcess::GetDllExport(m_pClientLogicDLL_Handle, *FuncNameDestroyClientLogic);
    JYLOG_PROCESS_ERROR(m_pFuncDestroyClientLogic);

    m_piClientLogic = m_pFuncCreateClientLogic();

    JY_STD_BOOL_END
}

void ClientLogic::UnInit()
{
    if (m_pClientLogicDLL_Handle)
    {
        if (m_pFuncDestroyClientLogic && m_piClientLogic)
            m_pFuncDestroyClientLogic(m_piClientLogic);

        FPlatformProcess::FreeDllHandle(m_pClientLogicDLL_Handle);
        m_pClientLogicDLL_Handle = NULL;
    }
}

bool ClientLogic::DoLoginRequest(int nTestNum)
{
    bool               bResult  = false;
    bool               bRetCode = false;
    GE2C_LOGIN_REQUEST Request;

    Request.wProtocolID = ege2c_login_request;
    Request.nTestNum    = nTestNum;

    bRetCode = m_piClientLogic->PushE2C((BYTE*)&Request, sizeof(Request));
    JYLOG_PROCESS_ERROR(bRetCode);

    JY_STD_BOOL_END
}