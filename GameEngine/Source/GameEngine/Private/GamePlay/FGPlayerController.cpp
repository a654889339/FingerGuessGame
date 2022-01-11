// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/FGPlayerController.h"

AFGPlayerController::AFGPlayerController()
{
    bShowMouseCursor = true;
}

void AFGPlayerController::BeginPlay()
{
    FInputModeUIOnly InputMode;

    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

    SetInputMode(InputMode);
}