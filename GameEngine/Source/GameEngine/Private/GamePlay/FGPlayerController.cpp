// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/FGPlayerController.h"

AFGPlayerController::AFGPlayerController()
{
    bShowMouseCursor = true;        //显示鼠标
}

void AFGPlayerController::BeginPlay()
{
    //用于设置仅允许UI响应用户输入的输入模式的数据结构
    FInputModeUIOnly InputMode;

    //设置鼠标的显示，将鼠标锁在界面中
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

    //将InputMode添加到 SetInputMode
    SetInputMode(InputMode);
}