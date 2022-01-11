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

    FString DllPath = "../../ThirdParty/Debug_X64/" + ClientLogicDllName;
    m_pClientLogic = FPlatformProcess::GetDllHandle(*DllPath);

    if (!m_pClientLogic)
    {
    }


}

void FGameEngineModule::ShutdownModule()
{
    if (m_pClientLogic)
    {
        FPlatformProcess::FreeDllHandle(m_pClientLogic);
        m_pClientLogic = NULL;
    }

    InitStyle::ShutDown();
}
