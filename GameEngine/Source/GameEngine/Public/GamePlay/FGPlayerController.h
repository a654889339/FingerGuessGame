// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GAMEENGINE_API AFGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    AFGPlayerController();        //显示鼠标

protected:
    virtual void BeginPlay() override;        //输入模式，UE4有4种输入模式，输入模式不能再构造函数里写

};
