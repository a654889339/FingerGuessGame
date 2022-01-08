// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Styling\SlateBrush.h"

/**
 * 
 */
class GAMEENGINE_API SInitMenuWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SInitMenuWidget)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

};
