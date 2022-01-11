// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"
#include "Styling/SlateBrush.h"

#include "InitMenuWidgetStyle.generated.h"

USTRUCT()
struct GAMEENGINE_API FInitMenuStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FInitMenuStyle& GetDefault();

    UPROPERTY(EditAnywhere, Category = MenuHUD)
        FSlateBrush MenuHUDBackgroundBrush;

    UPROPERTY(EditAnywhere, Category = Appearance)
        FTextBlockStyle MenuTitleStyle;

    UPROPERTY(EditAnywhere, Category = Appearance)
        FButtonStyle MenuButtonStyle;
};

UCLASS(hidecategories=Object, MinimalAPI)
class UInitMenuWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FInitMenuStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
