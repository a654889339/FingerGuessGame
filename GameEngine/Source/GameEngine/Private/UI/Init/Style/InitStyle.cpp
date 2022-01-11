// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Init/Style/InitStyle.h"
#include "Slate/SlateGameResources.h"

TSharedPtr<FSlateStyleSet> InitStyle::InitStyleInstance = NULL;

void InitStyle::Initialze()
{
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
    FSlateStyleRegistry::UnRegisterSlateStyle(*InitStyleInstance);

    ensure(InitStyleInstance.IsUnique());

    InitStyleInstance.Reset();
}

const ISlateStyle& InitStyle::Get()
{
    return *InitStyleInstance;
}

TSharedRef<class FSlateStyleSet> InitStyle::Create()
{
    TSharedRef<FSlateStyleSet> StyleRef = FSlateGameResources::New(InitStyle::GetStyleSetName(), "/Game/Levels/Init/Style", "/Game/Levels/Init/Style");

    return StyleRef;
}