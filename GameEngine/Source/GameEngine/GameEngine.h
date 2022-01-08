// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FGameEngineModule : public FDefaultGameModuleImpl
{
public:
    //模组加载时的方法
    virtual void StartupModule() override;

    //模组卸载时的方法
    virtual void ShutdownModule() override;
};