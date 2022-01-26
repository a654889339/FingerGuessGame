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

public:
    bool DoLoginRequest(int nTestNum);

private:
    IClientLogic*             m_piClientLogic;
    void*                     m_pClientLogicDLL_Handle;

    typedef IClientLogic* (*CREAT_CLIENT_LOGIC_FUNC)();
    typedef void (*DESTROY_CLIENT_LOGIC_FUNC)(IClientLogic* pClientLogic);
    CREAT_CLIENT_LOGIC_FUNC   m_pFuncCreateClientLogic;
    DESTROY_CLIENT_LOGIC_FUNC m_pFuncDestroyClientLogic;
};