// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../Base/ClientLogic/IClientLogic.h"
#include "../../Base/ClientLogic/CLIENT_GAME_ENGINE_PROTOCOL.h"

class ClientLogic
{
public:
    ClientLogic();
    ~ClientLogic();

    bool Init();
    void UnInit();

public:
    bool DoLoginRequest(int nTestNum);

private:
    void*                     m_pClientLogicDLL_Handle;
    IClientLogic*             m_piClientLogic;

    typedef IClientLogic* (*CREAT_CLIENT_LOGIC_FUNC)();
    typedef void (*DESTROY_CLIENT_LOGIC_FUNC)(IClientLogic* pClientLogic);
    CREAT_CLIENT_LOGIC_FUNC   m_pFuncCreateClientLogic;
    DESTROY_CLIENT_LOGIC_FUNC m_pFuncDestroyClientLogic;
};

static ClientLogic* g_pClient;