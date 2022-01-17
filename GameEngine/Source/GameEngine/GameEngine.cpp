// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameEngine.h"
#include "Modules/ModuleManager.h"
#include "UI/Init/Style/InitStyle.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FGameEngineModule, GameEngine, "GameEngine");

void FGameEngineModule::StartupModule()
{
    FSlateStyleRegistry::UnRegisterSlateStyle(InitStyle::GetStyleSetName());
    InitStyle::Initialze();

    FString ClientLogicDllName = TEXT("ClientX64D.dll");

    FString DllPath = "../../ThirdParty/Win64/" + ClientLogicDllName;
    m_pClientLogicDLL_Handle = FPlatformProcess::GetDllHandle(*DllPath);

    if (m_pClientLogicDLL_Handle)
    {
        FString FuncNameCreateClientLogic  = TEXT("CreateClientLogic");
        FString FuncNameDestroyClientLogic = TEXT("DestroyClientLogic");

        m_pFuncCreateClientLogic  = (CREAT_CLIENT_LOGIC_FUNC)  FPlatformProcess::GetDllExport(m_pClientLogicDLL_Handle, *FuncNameCreateClientLogic);
        m_pFuncDestroyClientLogic = (DESTROY_CLIENT_LOGIC_FUNC)FPlatformProcess::GetDllExport(m_pClientLogicDLL_Handle, *FuncNameDestroyClientLogic);
        if (m_pFuncCreateClientLogic && m_pFuncDestroyClientLogic)
        {
            m_pClientLogic = m_pFuncCreateClientLogic();
        }
    }
    else
    {

    }

}

void FGameEngineModule::ShutdownModule()
{
    if (m_pClientLogicDLL_Handle)
    {
        if (m_pFuncDestroyClientLogic && m_pClientLogic)
            m_pFuncDestroyClientLogic(m_pClientLogic);

        FPlatformProcess::FreeDllHandle(m_pClientLogicDLL_Handle);
        m_pClientLogicDLL_Handle = NULL;
    }

    InitStyle::ShutDown();
}
