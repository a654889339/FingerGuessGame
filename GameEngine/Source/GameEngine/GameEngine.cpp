// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameEngine.h"
#include "Modules/ModuleManager.h"
#include "UI/Init/Style/InitStyle.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FGameEngineModule, GameEngine, "GameEngine");

void FGameEngineModule::StartupModule()
{
    //初始化样式
    FSlateStyleRegistry::UnRegisterSlateStyle(InitStyle::GetStyleSetName());        //先取消注册
    InitStyle::Initialze();        //初始化
}

void FGameEngineModule::ShutdownModule()
{
    //注销
    InitStyle::ShutDown();
}
