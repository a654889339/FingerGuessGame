// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Base/IClientLogic.h"

class ClientLogic
{
public:
    ClientLogic();
    ~ClientLogic();

    bool Init();
    void UnInit();

public:
    typedef IClientLogic* (*CREAT_CLIENT_LOGIC_FUNC)();
    typedef void (*DESTROY_CLIENT_LOGIC_FUNC)(IClientLogic* pClientLogic);

    CREAT_CLIENT_LOGIC_FUNC   m_pFuncCreateClientLogic;
    DESTROY_CLIENT_LOGIC_FUNC m_pFuncDestroyClientLogic;

private:
    void*                     m_pClientLogicDLL_Handle;
    IClientLogic*             m_pClientLogic;
};

static ClientLogic* g_pClientLogic;