// Copyright Epic Games, Inc. All Rights Reserved.


#include "GameEngineGameModeBase.h"
#include "UI/Init/InitHUBBase.h"
#include "GamePlay/GamePlay.h"
#include "GamePlay/FGPlayerController.h"

AGameEngineGameModeBase::AGameEngineGameModeBase()
{
    PlayerControllerClass = AFGPlayerController::StaticClass();
    HUDClass = AInitHubBase::StaticClass();
}
