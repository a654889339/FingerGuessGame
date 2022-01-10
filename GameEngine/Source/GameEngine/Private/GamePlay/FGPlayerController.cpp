// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/FGPlayerController.h"

AFGPlayerController::AFGPlayerController()
{
    bShowMouseCursor = true;        //��ʾ���
}

void AFGPlayerController::BeginPlay()
{
    //�������ý�����UI��Ӧ�û����������ģʽ�����ݽṹ
    FInputModeUIOnly InputMode;

    //����������ʾ����������ڽ�����
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

    //��InputMode��ӵ� SetInputMode
    SetInputMode(InputMode);
}