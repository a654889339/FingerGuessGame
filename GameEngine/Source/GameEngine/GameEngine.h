// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FGameEngineModule : public FDefaultGameModuleImpl
{
public:
    //ģ�����ʱ�ķ���
    virtual void StartupModule() override;

    //ģ��ж��ʱ�ķ���
    virtual void ShutdownModule() override;
};