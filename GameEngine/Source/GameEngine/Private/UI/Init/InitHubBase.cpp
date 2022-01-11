// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Init/InitHubBase.h"
#include "UI/Init/Widget/SInitMenuHUBWidget.h"
#include "SlateBasics.h"

AInitHUBBase::AInitHUBBase()
{
    if (GEngine && GEngine->GameViewport)
    {
        SAssignNew(MenuHUDWidget, SInitMenuHUBWidget);

        GEngine->GameViewport->AddViewportWidgetContent
        (
            SNew(SWeakWidget).PossiblyNullContent(MenuHUDWidget.ToSharedRef())
        );
    }
}