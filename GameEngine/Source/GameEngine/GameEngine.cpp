#include "GameEngine.h"

#include "Base/stdafx.h"
#include "Modules/ModuleManager.h"
#include "UI/Init/Style/InitStyle.h"
#include "InitClientLogic.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FGameEngineModule, GameEngine, "GameEngine");

void FGameEngineModule::StartupModule()
{
    FSlateStyleRegistry::UnRegisterSlateStyle(InitStyle::GetStyleSetName());
    InitStyle::Initialze();

    InitClientLogic::Initialze();
}

void FGameEngineModule::ShutdownModule()
{
    InitClientLogic::ShutDown();
    InitStyle::ShutDown();
}
