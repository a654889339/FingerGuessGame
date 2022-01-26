// Fill out your copyright notice in the Description page of Project Settings.


#include "InitClientLogic.h"

TSharedPtr<ClientLogic> InitClientLogic::ClientLogicInstance = NULL;


void InitClientLogic::Initialze()
{
    if (!ClientLogicInstance.IsValid())
    {
        ClientLogicInstance = Create();
    }
}

void InitClientLogic::ShutDown()
{
    ensure(ClientLogicInstance.IsUnique());

    ClientLogicInstance.Reset();
}

ClientLogic& InitClientLogic::Get()
{
    return *ClientLogicInstance;
}

TSharedRef<class ClientLogic> InitClientLogic::Create()
{
    TSharedRef<ClientLogic> NewClientLogic = MakeShareable(new ClientLogic());

    return NewClientLogic;
}