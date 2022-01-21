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

    m_pClientLogic = m_pFuncCreateClientLogic();

    JY_STD_BOOL_END
}

void ClientLogic::UnInit()
{
    if (m_pClientLogicDLL_Handle)
    {
        if (m_pFuncDestroyClientLogic && m_pClientLogic)
            m_pFuncDestroyClientLogic(m_pClientLogic);

        FPlatformProcess::FreeDllHandle(m_pClientLogicDLL_Handle);
        m_pClientLogicDLL_Handle = NULL;
    }
}
