// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FGPlayerController.generated.h"

UCLASS()
class GAMEENGINE_API AFGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    AFGPlayerController();        //��ʾ���

protected:
    virtual void BeginPlay() override;        //����ģʽ��UE4��4������ģʽ������ģʽ�����ٹ��캯����д

};
