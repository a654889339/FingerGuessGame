// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientLogic.h"

class GAMEENGINE_API InitClientLogic
{
public:
    static void Initialze();
    static void ShutDown();

    static const ClientLogic& Get();

private:
    static TSharedRef<class ClientLogic> Create();

    static TSharedPtr<ClientLogic> ClientLogicInstance;
};
