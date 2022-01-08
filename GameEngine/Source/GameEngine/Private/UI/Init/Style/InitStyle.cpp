// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Init/Style/InitStyle.h"
#include "Slate/SlateGameResources.h"

TSharedPtr<FSlateStyleSet> InitStyle::InitStyleInstance = NULL;

void InitStyle::Initialze()
{
    //注册 InitStyleInstance 具体为啥需要看下源码
    if (!InitStyleInstance.IsValid())
    {
        InitStyleInstance = Create();
        FSlateStyleRegistry::RegisterSlateStyle(*InitStyleInstance);
    }
}

FName InitStyle::GetStyleSetName()
{
    static FName StyleSetName(TEXT("InitStyle"));
    return StyleSetName;
}

void InitStyle::ShutDown()
{
    //取消注册
    FSlateStyleRegistry::UnRegisterSlateStyle(*InitStyleInstance);

    //确保是唯一的
    ensure(InitStyleInstance.IsUnique());

    //重置
    InitStyleInstance.Reset();
}

const ISlateStyle& InitStyle::Get()
{
    return *InitStyleInstance;
}

TSharedRef<class FSlateStyleSet> InitStyle::Create()
{
    //BPInitMenuStyle蓝图所存放的路径
    TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(InitStyle::GetStyleSetName(), "/Game/Levels/Init/Style", "/Game/Levels/Init/Style");

    return StyleRef;
}