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
    MenuStyle = &InitStyle::Get().GetWidgetStyle<FInitMenuStyle>("BPInitMenuStyle");

    ChildSlot
    [
        SNew(SOverlay)

        // ±³¾°Í¼
        + SOverlay::Slot()   //Slot Ìí¼Ó²å²Û
        .HAlign(HAlign_Fill) //*_Fill Ìî³ä
        .VAlign(VAlign_Fill)
        [
            SNew(SImage).Image(&MenuStyle->MenuHUDBackgroundBrush)
        ]

        + SOverlay::Slot()
        .HAlign(HAlign_Right)
        .VAlign(VAlign_Bottom)
        [
            SNew(SVerticalBox)
            + SVerticalBox::Slot()
            [
                SNew(SButton)
                .ButtonStyle(&MenuStyle->MenuButtonStyle)
                .Text(FText::FromString("Play Game!"))
                .OnClicked(this, &SInitMenuHUBWidget::Login)
            ]
        ]
    ];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SInitMenuHUBWidget::Login()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("Click Login"));
    }

    return FReply::Handled();
}