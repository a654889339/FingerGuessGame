// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"

class GAMEENGINE_API InitStyle
{
public:
    static void Initialze();
    static void ShutDown();

    static FName GetStyleSetName();

    static const ISlateStyle& Get();

private:
    static TSharedRef<class FSlateStyleSet> Create();

    static TSharedPtr<FSlateStyleSet> InitStyleInstance;
};
