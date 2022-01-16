// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameEngine.h"
#include "Modules/ModuleManager.h"
#include "UI/Init/Style/InitStyle.h"
#include "../../ThirdParty/Include/IClientLogic.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FGameEngineModule, GameEngine, "GameEngine");

void FGameEngineModule::StartupModule()
{
    FSlateStyleRegistry::UnRegisterSlateStyle(InitStyle::GetStyleSetName());
    InitStyle::Initialze();

    FString ClientLogicDllName = TEXT("ClientX64D.dll");

    FString DllPath = "../../ThirdParty/Debug_X64/" + ClientLogicDllName;
    m_pClientLogicDLL_Handle = FPlatformProcess::GetDllHandle(*DllPath);

    if (m_pClientLogicDLL_Handle)
    {
        typedef IClientLogic* (*CREAT_CLIENT_LOGIC_FUNC)();

        CREAT_CLIENT_LOGIC_FUNC CreateClientLogicFunc = (CREAT_CLIENT_LOGIC_FUNC)FPlatformProcess::GetDLLExport(m_pClientLogicDLL_Handle, "CreateClientLogic");
        if (CreateClientLogicFunc)
        {
            IClientLogic* m_pClientLogic = CreateClientLogicFunc();
            if (m_pClientLogic)
                m_pClientLogic->Init();
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
        FPlatformProcess::FreeDllHandle(m_pClientLogicDLL_Handle);
        m_pClientLogicDLL_Handle = NULL;
    }

    InitStyle::ShutDown();
}
