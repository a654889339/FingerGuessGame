// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Init/Style/InitMenuWidgetStyle.h"

const FName FInitMenuStyle::TypeName(TEXT("FInitMenuStyle"));

const FInitMenuStyle& FInitMenuStyle::GetDefault()
{
	static FInitMenuStyle Default;
	return Default;
}

void FInitMenuStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
}

