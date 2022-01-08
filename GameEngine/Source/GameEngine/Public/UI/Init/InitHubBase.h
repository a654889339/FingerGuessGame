// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InitHubBase.generated.h"

/**
 * 
 */
UCLASS()
class GAMEENGINE_API AInitHUBBase : public AHUD
{
	GENERATED_BODY()

public:
    AInitHUBBase();
    TSharedPtr<class SInitMenuHUBWidget> MenuHUDWidget;
};
