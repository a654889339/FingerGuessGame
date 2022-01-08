// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/GameEngineGameMode.h"
#include "UI/Init/InitHUBBase.h"
#include "GamePlay/FGPlayerController.h"

AGameEngineGameMode::AGameEngineGameMode()
{
    PlayerControllerClass = AFGPlayerController::StaticClass();
    HUDClass = AInitHUBBase::StaticClass();
}
