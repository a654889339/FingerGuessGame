// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameEngine.h"
#include "Modules/ModuleManager.h"
#include "UI/Init/Style/InitStyle.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FGameEngineModule, GameEngine, "GameEngine");

void FGameEngineModule::StartupModule()
{
    //��ʼ����ʽ
    FSlateStyleRegistry::UnRegisterSlateStyle(InitStyle::GetStyleSetName());        //��ȡ��ע��
    InitStyle::Initialze();        //��ʼ��
}

void FGameEngineModule::ShutdownModule()
{
    //ע��
    InitStyle::ShutDown();
}
