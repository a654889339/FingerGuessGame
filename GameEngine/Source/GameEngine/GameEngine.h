// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FGameEngineModule : public FDefaultGameModuleImpl
{
public:
    virtual void StartupModule() override;

    virtual void ShutdownModule() override;

public:
    void* m_pClientLogicDLL_Handle = nullptr;
};