#include "GameEngine.h"

#include "Base/stdafx.h"
#include "Modules/ModuleManager.h"
#include "UI/Init/Style/InitStyle.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FGameEngineModule, GameEngine, "GameEngine");

void FGameEngineModule::StartupModule()
{
    bool bRetCode = false;

    FSlateStyleRegistry::UnRegisterSlateStyle(InitStyle::GetStyleSetName());
    InitStyle::Initialze();

    bRetCode = m_ClientLogic.Init();
    JYLOG_PROCESS_ERROR(bRetCode);

    g_pClient = &m_ClientLogic;

    JY_STD_VOID_END
}

void FGameEngineModule::ShutdownModule()
{
    g_pClient = NULL;
    m_ClientLogic.UnInit();
    InitStyle::ShutDown();
}
