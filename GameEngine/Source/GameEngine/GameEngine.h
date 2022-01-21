// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ClientLogic.h"

class FGameEngineModule : public FDefaultGameModuleImpl
{
public:
    virtual void StartupModule() override;

    virtual void ShutdownModule() override;

public:
    ClientLogic m_ClientLogic;
};