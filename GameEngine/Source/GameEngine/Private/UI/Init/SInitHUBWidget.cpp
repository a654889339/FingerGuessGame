// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Init/SInitHUBWidget.h"
#include "SlateOptMacros.h"
#include "Widgets/Input/SButton.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SInitHUBWidget::Construct(const FArguments& InArgs)
{
    ChildSlot //ChildSlot 是层级一样的东西
    [
        SNew(SButton)
    ];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
