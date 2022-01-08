// Fill out your copyright notice in the Description page of Project Settings.


#include "SlateOptMacros.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Images/SImage.h"

#include "UI/Init/Widget/SInitMenuHUBWidget.h"
#include "UI/Init/Style/InitStyle.h"
#include "UI/Init/Style/InitMenuWidgetStyle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SInitMenuHUBWidget::Construct(const FArguments& InArgs)
{
    InitMenuHUB = InArgs._InitMenuHUB;
    MenuStyle = &InitStyle::Get().GetWidgetStyle<FInitMenuStyle>("BPInitMenuStyle");
    ChildSlot
    [
        SNew(SImage)
        .Image(&MenuStyle->MenuHUDBackgroundBrush)
    ];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
