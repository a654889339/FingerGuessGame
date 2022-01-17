// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "../../../Client/DLL/IClientLogic.h"

class FGameEngineModule : public FDefaultGameModuleImpl
{
public:
    typedef IClientLogic* (*CREAT_CLIENT_LOGIC_FUNC)();
    typedef void (*DESTROY_CLIENT_LOGIC_FUNC)(IClientLogic* pClientLogic);

    virtual void StartupModule() override;

    virtual void ShutdownModule() override;

public:
    void*                     m_pClientLogicDLL_Handle = nullptr;
    CREAT_CLIENT_LOGIC_FUNC   m_pFuncCreateClientLogic;
    DESTROY_CLIENT_LOGIC_FUNC m_pFuncDestroyClientLogic;
    IClientLogic*             m_pClientLogic;
};